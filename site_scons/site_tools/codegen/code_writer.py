# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of
# the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from collections import defaultdict
try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO
import os
import sys
import re

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "site_packages"))

import cantools

"""
References:
    https://cantools.readthedocs.io/en/latest/#cantools.database.can.Message
    https://cantools.readthedocs.io/en/latest/#cantools.database.can.Signal
"""

ENUM_SUFFIX = "_e"
GENERATE_ALL_NODE_NAME = "ALL"


class InvalidDBCNodeError(Exception):
    pass


class CodeWriter(object):
    def __init__(self, dbc_filepath, dbc_node_name, generate_enum_code=True):
        self._stream = StringIO()
        self._dbc_node_name = dbc_node_name
        self._generate_enum_code = generate_enum_code

        self._dbc_filepath = dbc_filepath
        self._dbc = cantools.database.load_file(dbc_filepath)
        self._valid_node_names = list(map(lambda node: node.name, self._dbc.nodes))

        if (self._dbc_node_name != GENERATE_ALL_NODE_NAME) and (self._dbc_node_name not in self._valid_node_names):
            raise InvalidDBCNodeError("Invalid node [{}]! Available nodes {}".format(self._dbc_node_name, self._valid_node_names))

        self._file_header()
        self._common_structs()
        self._generate_enums()

        self._message_header_instances()
        self._structs()

        self._seperator("Missing in Action (MIA) user dependencies")
        self._mia_user_dependencies()

        self._seperator("Encode methods")
        self._encode_methods()

        self._seperator("Decode methods")
        self._decode_methods()

        self._seperator("MIA methods")
        self._mia_methods()

        self._write_footer()

    def __str__(self):
        return self._stream.getvalue()

    """
    Private methods
    """

    def _seperator(self, title):
        self._stream.write((
            "/************************************************************************\n"
            " ********* {0}\n"
            " ************************************************************************/\n\n"
        ).format(title))

    def _file_header(self):
        dbc_filename = os.path.basename(self._dbc_filepath)

        self._stream.write((
            "// clang-format off\n"
            "// AUTO-GENERATED - DO NOT EDIT\n"
            "// Generated from {0}\n"
            "#pragma once\n"
            "\n"
            "#include <stdbool.h>\n"
            "#include <stdint.h>\n"
            "#include <string.h>\n"
            "\n"
            "#ifndef MIN_OF\n"
            "#define MIN_OF(x,y) ((x) < (y) ? (x) : (y))\n"
            "#endif\n"
            "#ifndef MAX_OF\n"
            "#define MAX_OF(x,y) ((x) > (y) ? (x) : (y))\n"
            "#endif\n"
            "\n"
            "/**\n"
            " * Extern dependency to use dbc_encode_and_send_*() API\n"
            " * This is designed such that the generated code does not depend on your CAN driver\n"
            " * @param argument_from_dbc_encode_and_send is a pass through argument from dbc_encode_and_send_*()\n"
            " * @returns the value returned from is returned from dbc_encode_and_send_*()\n"
            " */\n"
            "extern bool dbc_send_can_message(void * argument_from_dbc_encode_and_send, uint32_t message_id, const uint8_t bytes[8], uint8_t dlc);\n"
            "\n"
        ).format(dbc_filename))

    def _write_footer(self):
        self._stream.write( "// clang-format off")

    def _common_structs(self):
        self._stream.write(
            "/// Missing in Action (MIA) structure\n"
            "typedef struct {\n"
            "  uint32_t mia_counter; ///< Counter used to track MIA\n"
            "} dbc_mia_info_t;\n"
            "\n"
            "/**\n"
            " * dbc_encode_*() API returns this instance to indicate message ID and DLC that should be used\n"
            " * dbc_decode_*() API checks against the provided header to make sure we are decoding the right message\n"
            " */\n"
            "typedef struct {\n"
            "  uint32_t message_id;  ///< CAN bus message identification\n"
            "  uint8_t message_dlc;  ///< Data Length Code of the CAN message\n"
            "} dbc_message_header_t;\n"
        )

    def _mia_user_dependencies(self):
        line = ("// " + "-"*(80-3) + "\n")

        self._stream.write("\n")
        self._stream.write(line)
        self._stream.write("// When a message's MIA counter reaches this value\n"
                           "// corresponding MIA replacements occur\n")
        self._stream.write(line)
        for message in self._dbc.messages:
            self._stream.write("extern const uint32_t dbc_mia_threshold_{0};\n".format(message.name))

        self._stream.write("\n")
        self._stream.write(line)
        self._stream.write("// User must define these externed instances in their code to use MIA functions\n")
        self._stream.write("// These are copied during dbc_service_mia_*() when message MIA timeout occurs\n")
        self._stream.write(line)
        for message in self._dbc.messages:
            suggested_mia_time = "" if message.cycle_time == 0 else (" // Suggested MIA threshold: (3*{0})".format(message.cycle_time))
            self._stream.write(("extern const dbc_{0}_s ".format(message.name)).ljust(40))
            self._stream.write("dbc_mia_replacement_{0};{1}\n".format(message.name, suggested_mia_time))

        self._stream.write("\n")

    def _generate_enums(self):
        if not self._generate_enum_code:
            return

        code = ""
        choices = {}

        for message in self._dbc.messages:
            for signal in message.signals:
                if signal.choices is not None:
                    choices[signal.name] = signal.choices

        # signal_name is the key',
        # enum_list is:
        # OrderedDict([(2, 'DRIVER_HEARTBEAT_cmd_REBOOT'), (1, 'DRIVER_HEARTBEAT_cmd_SYNC'), (0, 'DRIVER_HEARTBEAT_cmd_NOOP')])
        for signal_name, enum_list in choices.items():
            values = ""
            for value, enum_item_name in enum_list.items():
                reformatted_item_name = re.sub('[^0-9a-zA-Z]+', '_', enum_item_name)
                values += "  {0}__{1} = {2},\n".format(signal_name, reformatted_item_name, value)

            code += (
                "\n"
                "// Enumeration for {0}\n"
                "typedef enum {{\n"
                "{1}"
                "}} {2}{3};\n"
            ).format(signal_name, values, signal_name, ENUM_SUFFIX)

        code += "\n"
        self._stream.write(code)

    def _message_header_instances(self):
        self._stream.write('// Message headers containing CAN message IDs and their DLCs; @see dbc_message_header_t\n')
        for message in self._dbc.messages:
            self._stream.write('static const dbc_message_header_t dbc_header_{0}'.format(message.name).ljust(80))
            self._stream.write(' = {{ {1}U, {2} }};\n'.format(
                message.name, str(message.frame_id).rjust(8), message.length))

    def _structs(self):
        for message in self._dbc.messages:
            signal_members = self._generate_struct_signals(message)

            # MIA only makes sense for messages we receive, and not the messages we send
            mia = "  dbc_mia_info_t mia_info;\n"
            comment = "" if message.comment is None else ("\n *   - "+message.comment)
            cycle_time = "" if message.cycle_time == 0 else ("\n *   - Expected every {0} ms".format(message.cycle_time))

            # Ask the CANtools to dump the layout of the message for visual purpose
            self._stream.write("\n")
            self._stream.write("/* " + "*"*80 + "*/\n")
            self._stream.write("#if 0 /* Layout of {0} */\n".format(message.name))
            self._stream.write(message.layout_string())
            self._stream.write("\n#endif\n")

            self._stream.write((
                "/**\n"
                " * {0}: Sent by '{1}'{2}{3}\n"
                " */\n"
                "typedef struct {{\n"
                "{4}"
                "\n"
                "{5}}} dbc_{0}_s;\n"
            ).format(message.name, self._get_sender(message), comment, cycle_time, mia, signal_members))
        self._stream.write("\n")

    def _decode_methods(self):
        for message in self._dbc.messages:
            validation_check = (
                "  if ((header.message_id != dbc_header_{0}.message_id) || (header.message_dlc != dbc_header_{1}.message_dlc)) {{\n"
                "    return !success;\n"
                "  }}\n"
            ).format(message.name, message.name)

            self._stream.write((
                "/**\n"
                " * Decode received message {0}: Sent by {1}\n"
                " *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success\n"
                " */\n"
                "static inline bool dbc_decode_{0}(dbc_{0}_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {{\n"
                "  const bool success = true;\n"
                "{2}\n"
                "{3}\n"
                "\n"
                "  message->mia_info.mia_counter = 0;\n"
                "  return success;\n"
                "}}\n"
            ).format(message.name, self._get_sender(message), validation_check, self._get_decode_code_for_message(message)))

        self._stream.write("\n")

    def _get_decode_code_for_message(self, message):
        code = "  uint64_t raw = 0;\n"

        if message.is_multiplexed():
            code += "  // Multiplexed signals are not handled yet\n"
            code += "  (void)raw;\n"
        else:
            for signal in message.signals:
                code += self._get_decode_code_for_signal(signal)
                code += '\n'

        # Remove excessive newlines from the end
        return code.rstrip()

    def _get_decode_code_for_signal(self, signal, raw_sig_name="raw"):
        code = self._get_decode_bitmasking_code_for_signal(signal, raw_sig_name)

        signal_scale, signal_offset = self._get_scale_and_offset_with_casts(signal)

        enum_cast = "";
        if self._generate_enum_code and self._is_signal_an_enum(signal):
            enum_cast = '({0})'.format(self._get_signal_type(signal))

                # If the signal is not defined as a signed, then we will use this code
        unsigned_code = "message->{0} = {1}(({2} * {3}) + ({4}));".format(signal.name, enum_cast, raw_sig_name,
                                                                             signal_scale, signal_offset)

        if signal.is_signed:
            s =  "  if ({0} & (1 << {1})) {{ // Check signed bit of the raw DBC signal and sign extend from 'raw'\n".format(raw_sig_name, (signal.length - 1))
            s += "    message->{0} = ".format(signal.name)

            # Create signed extended number by first getting a type similar to '(int16_t)-1'
            # The only corner case is that this will not work for float, but float should not
            # be listed as a signed number
            # TODO: Should we always use `int32_t` cast here?
            s += "((int32_t)((~0U << {0}) | {1}) * {2}) + ({3});\n".format(
                str(signal.length - 1), raw_sig_name, signal_scale, signal_offset
            )

            s += ("  }} else {{\n"
                  "    {0} // Copy unsigned raw number\n"
                  "  }}\n").format(unsigned_code)
        else:
            s = "  " + unsigned_code + "\n"

        # Optimize
        s = s.replace(" + (0)", "")
        s = s.replace(" + ((float)0)", "") # ((raw * (float)0.1) + ((float)0));
        s = s.replace(" * 1)", ")")
        s = s.replace(" * (float)1)", ")") # ((raw * (float)1) + ((float)10));
        s = s.replace("(raw)", "raw")
        s = s.replace("(raw)", "raw") # If no offset and scale, it turns out to be `((raw))`
        
        code += s

        return code

    def _get_decode_bitmasking_code_for_signal(self, signal, raw_sig_name):
        code = ""
        signal_start = self._get_the_truly_honest_start_bit(signal)
        raw_sig_bit_position = signal_start
        remaining = signal.length
        byte_num = int(signal_start / 8)
        bit_count = 0

        if not self._is_signal_little_endian(signal):
            code += "  // Note that this Big-Endian defines DBC bit {0}, and actual signal starts at byte[{1}], bit({2})\n".format(
                        signal.start, str(signal_start//8), str(signal_start % 8))

        while remaining > 0:
            bits_in_this_byte = min(8 - (raw_sig_bit_position % 8), remaining)

            s = ""
            s += "  {0} |= (uint64_t)((bytes[{1}] >> {2})".format(raw_sig_name, byte_num, (raw_sig_bit_position % 8))
            s += " & 0x{0}) << {1}".format(format(2 ** bits_in_this_byte - 1, '02x'), bit_count)
            s += "; // extract {0} bit(s) to bit position {1}\n".format(str(bits_in_this_byte), bit_count)

            # Optimize
            s = self._optimize_shifts(s)
            s = s.replace(" & 0xff", "")
            code += s

            if bit_count == 0:
                code = code.replace("|= (uint64_t)", "= ")

            byte_num = self._get_next_byte_number(signal, byte_num)
            raw_sig_bit_position += bits_in_this_byte
            remaining -= bits_in_this_byte
            bit_count += bits_in_this_byte
        
        return code

    def _encode_methods(self):
        for message in self._dbc.messages:
            if not self._message_is_relevant(message):
                self._stream.write(("/**\n"
                                       " * {0}:\n"
                                       " *   Transmitter: '{1}' with message ID {2} composed of {3} bytes\n"
                                       " *   **Since you ({4}) are not the transmitter, this function is not generated for you**\n"
                                       " */\n"
                                       "// static inline dbc_message_header_t dbc_encode_{0}(uint8_t bytes[8], const dbc_{0}_s *message);\n"
                                   ).format(message.name, self._get_sender(message), message.frame_id, message.length, self._dbc_node_name.upper()))
            else:
                encode_code = self._get_encode_code_for_message(message)

                self._stream.write((
                    "/**\n"
                    " * Encode to transmit {0}:\n"
                    " *   Transmitter: '{1}' with message ID {2} composed of {3} bytes\n"
                    " */\n"
                    "static inline dbc_message_header_t dbc_encode_{0}(uint8_t bytes[8], const dbc_{0}_s *message) {{\n"
                    "{4}\n"
                    "\n"
                    "  return dbc_header_{0};\n"
                    "}}\n"
                ).format(message.name, self._get_sender(message), message.frame_id, message.length, encode_code))
    
                self._stream.write((
                    "\n"
                    "/// @see dbc_encode_{0}(); this is its variant to encode and call dbc_send_can_message() to send the message\n"
                    "static inline bool dbc_encode_and_send_{0}(void *argument_for_dbc_send_can_message, const dbc_{0}_s *message) {{\n"
                    "  uint8_t bytes[8];\n"
                    "  const dbc_message_header_t header = dbc_encode_{0}(bytes, message);\n"
                    "  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);\n"
                    "}}\n"
                ).format(message.name))

                self._stream.write("\n")

    def _get_encode_code_for_message(self, message):
        code = "  uint64_t raw = 0;\n"\
               "  memset(bytes, 0, 8);\n"\
               "\n"

        if message.is_multiplexed():
            code += "  // Multiplexed signals are not handled yet\n"
        else:
            for signal in message.signals:
                code += self._get_encode_code_for_signal(signal, "raw")
                code += '\n'

        # Remove excessive newlines from the end
        return code.rstrip()

    def _get_encode_signal_comment(self, signal):
        offset_string = ""
        if signal.offset != 0:
            offset_string = " and offset={0}".format(signal.offset)

        min_max_comment = ""
        if not (signal.minimum is None and signal.maximum is None):
            min_max_comment = " within range of [{0} -> {1}]".format(signal.minimum, signal.maximum)

        signal_comment = ""
        if signal.is_signed:
            signal_comment = "  // Encode to raw {0}-bit SIGNED signal with scale={1}{2}{3}\n".format(signal.length, signal.scale, offset_string, min_max_comment)
        else:
            signal_comment = "  // Encode to raw {0}-bit signal with scale={1}{2}{3}\n".format(signal.length, signal.scale, offset_string, min_max_comment)

        return signal_comment

    def _get_encode_code_for_signal(self, signal, raw_sig_name):
        # TODO: Need to add rounding offeset
        if signal.scale != 1:
            pass

        signal_is_float = self._get_signal_type(signal) == "float"
        signal_scale, signal_offset = self._get_scale_and_offset_with_casts(signal)

        # Cast to int64_t or higher type may be required because we may have int8_t signal with
        # value of 100, with an offset of -200 which will roll over and produce incorrect result
        cast = self._get_signal_upcast_type(signal) if signal.offset != 0 else ""

        # Get the formula to convert signal to raw signal
        # We may have to apply the min/max in place of the `?` hence leave this as a placeholder
        scale_and_offset = "((? - ({0})) / {1})".format(signal_offset, signal_scale)

        # Optimize the equation of `- ({0})) / {1}`
        scale_and_offset = scale_and_offset.replace(" - (0)", "")
        scale_and_offset = scale_and_offset.replace(" - ((float)0)", "")
        scale_and_offset = scale_and_offset.replace(" / 1)", ")")
        scale_and_offset = scale_and_offset.replace(" / (float)1)", ")")

        signal_struct_accessor = "{0}message->{1}".format(cast, signal.name)
        if signal.minimum is None and signal.maximum is None:
            # signal_struct_accessor remains as-is
            pass
        else:
            # When using MIN_OF/MAX_OF macros, we need to use 'f' notation to explicitly use float rather than double
            minimum = "(float)" + str(signal.minimum) if signal_is_float else str(signal.minimum)
            maximum = "(float)" + str(signal.maximum) if signal_is_float else str(signal.maximum)
            signal_struct_accessor = "MAX_OF(MIN_OF({0},{1}),{2})".format(signal_struct_accessor, maximum, minimum)

        # Replace the missing '?' in the string with struct accessor which could have min/max formula
        signal_accessor_with_scale_and_offset = scale_and_offset.replace("?", signal_struct_accessor)

        mask = "0x{0}".format(format(2 ** signal.length - 1, '02x'))
        signal_to_raw = ("  {0} = (uint64_t){1} & {2};\n").format(raw_sig_name, signal_accessor_with_scale_and_offset, mask)

        # Add comment and code that extracts struct signal to raw value
        code = self._get_encode_signal_comment(signal) + signal_to_raw

        # Generate code that processes raw value and stuff it into CAN message bytes
        code += self._get_encode_bitmasking_code_for_signal(signal, raw_sig_name)

        return code

    def _get_encode_bitmasking_code_for_signal(self, signal, raw_sig_name):
        code = ""

        signal_start = self._get_the_truly_honest_start_bit(signal)
        raw_sig_bit_position = signal_start
        remaining = signal.length
        byte_num = int(signal_start / 8)

        if not self._is_signal_little_endian(signal):
            code += "  // Note that this Big-Endian defines DBC bit {0}, and actual signal starts at byte[{1}], bit({2})\n".format(
                signal.start, str(signal_start//8), str(signal_start % 8))

        while remaining > 0:
            bits_in_this_byte = min(8 - (raw_sig_bit_position % 8), remaining)
            bit_position = raw_sig_bit_position - signal_start

            s = ""
            s += "  bytes[{0}] |= (((uint8_t)({1} >> {2})".format(byte_num, raw_sig_name, bit_position)
            s += " & 0x{0}) << {1})".format(format(2 ** bits_in_this_byte - 1, '02x'), str(raw_sig_bit_position % 8))
            s += "; // write {0} bit(s) from bit position {1}\n".format(str(bits_in_this_byte), bit_position)

            # Optimize
            s = self._optimize_shifts(s)
            code += s

            # Cannot optimize by removing 0xff just for code safety
            # s = s.replace(" & 0xff", "")

            byte_num = self._get_next_byte_number(signal, byte_num)
            raw_sig_bit_position += bits_in_this_byte
            remaining -= bits_in_this_byte

        return code

    def _mia_methods(self):
        self._stream.write(
            "// Do not use this function\n"
            "static inline bool dbc_service_mia_for(dbc_mia_info_t *mia_info, const uint32_t increment_mia_by, const uint32_t threshold) {\n"
            "  bool message_just_entered_mia = false;\n"
            "\n"
            "  if (mia_info->mia_counter >= threshold) {\n"
            "    // Message is already MIA\n"
            "  } else {\n"
            "    mia_info->mia_counter += increment_mia_by;\n"
            "    message_just_entered_mia = (mia_info->mia_counter >= threshold);\n"
            "  }\n"
            "\n"
            "  return message_just_entered_mia;\n"
            "}\n"
            "\n"
        )

        for message in self._dbc.messages:
            self._stream.write("static inline bool dbc_service_mia_{0}(dbc_{0}_s *message, const uint32_t increment_mia_by) {{\n"
                               "  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_{0});\n"
                               "\n"
                               "  if (message_just_entered_mia) {{\n"
                               "    const dbc_mia_info_t previous_mia = message->mia_info;\n"
                               "    *message = dbc_mia_replacement_{0};\n"
                               "    message->mia_info = previous_mia;\n"
                               "  }}\n"
                               "\n"
                               "  return message_just_entered_mia;\n"
                               "}}\n"
                               "\n".format(message.name)
                               )

    def _generate_struct_signals(self, message):
        signals_string = ""

        if not message.is_multiplexed():
            signals_list = []
            for signal in message.signals:
                type_and_name = "{0} {1}".format(self._get_signal_type(signal), signal.name)

                comment = "" if signal.comment is None else signal.comment
                comment += "" if signal.unit is None else (" unit: " + signal.unit)
                if len(comment) > 0:
                    comment = (' // ' + comment).replace('  ', ' ')

                signal = "  {0};{1}\n".format(type_and_name, comment)
                signals_list.append(signal)
            
            signals_list.sort()
            signals_string += ''.join(signals_list)
        else:
            # For a muxed message, first generate non-mux symbols (which includes the mux itself)
            for signal in message.signals:
                if signal.multiplexer_ids is None:
                    type_and_name = "{0} {1}".format(self._get_signal_type(signal), signal.name)
                    signals_string += "  {0}; // Non-muxed signal\n".format(type_and_name)

            # Create a dictionary of a list where the key is the mux symbol
            muxed_signals = self._get_muxed_signals(message)

            for mux_id in muxed_signals:
                signals_string += '\n'
                for signal in muxed_signals[mux_id]:
                    type_and_name = "{0} {1}".format(self._get_signal_type(signal), signal.name)
                    signals_string += "  {0}; // M{1}\n".format(type_and_name, mux_id)

        return signals_string

    def _get_next_byte_number(self, signal, byte_number):
        return byte_number + 1 if self._is_signal_little_endian(signal) else byte_number - 1

    def _optimize_shifts(self, s):
        s = s.replace(" >> 0", "")
        s = s.replace(" << 0", "")
        s = s.replace("(raw)", "raw")
        return s

    def _get_scale_and_offset_with_casts(self, signal):
        signal_scale = signal.scale
        signal_offset = signal.offset

        signal_is_float = self._get_signal_type(signal) == "float"
        if signal_is_float:
            signal_scale = "(float)" + str(signal.scale)
            signal_offset = "(float)" + str(signal.offset)

        return signal_scale, signal_offset

    def _get_the_truly_honest_start_bit(self, signal):
        '''
        Little Endian starts at 'signal.start' as usual, but for Big Endian we need to determine the real 'start bit'
        In the DBC, the Big Endian "start bit" is actually the ending (MSB) bit
        '''
        start_bit = signal.start

        # Big Endian borrowed from:
        # https://github.com/ebroecker/SocketCandecodeSignals/blob/master/datenbasis.c#L112-L122
        if not self._is_signal_little_endian(signal):
            pos = 7 - (signal.start % 8) + (signal.length - 1)
            if pos < 8:
                start_bit = start_bit - signal.length + 1;
            else:
                cpos = 7 - (pos % 8)
                bytes = (pos // 8)
                start_bit = cpos + (bytes * 8) + (start_bit//8) * 8;

        return start_bit

    def _get_muxed_signals(self, message):
        # Create a dictionary of a list where the key is the mux symbol
        muxed_signals = defaultdict(list)

        for signal in message.signals:
            if signal.multiplexer_ids is not None:
                muxed_signals[signal.multiplexer_ids[0]].append(signal)

        return muxed_signals

    def _get_signal_upcast_type(self, signal):
        signal_type = "";

        if self._generate_enum_code and self._is_signal_an_enum(signal):
            signal_type = "" # Enum needs no cast
        elif (signal.scale * 1.0).is_integer():
            max_value = (2 ** signal.length) * signal.scale
            if signal.is_signed:
                max_value *= 2

            signal_type = "(uint32_t)"
            if max_value <= 256:
                signal_type = "(uint16_t)"
            elif max_value <= 65536:
                signal_type = "(uint32_t)"

            # If the signal is signed, or the offset is negative, remove "u" to use "int" type.
            if signal.is_signed or signal.offset < 0:
                signal_type = signal_type.replace("uint", "int")
        else:
            signal_type = "" # float

        return signal_type

    def _get_signal_type(self, signal):
        signal_type = "float";

        if self._generate_enum_code and self._is_signal_an_enum(signal):
            signal_type = signal.name + ENUM_SUFFIX
        elif (signal.scale * 1.0).is_integer() and (signal.offset * 1.0).is_integer():
            max_value = (2 ** signal.length) * signal.scale
            if signal.is_signed:
                max_value *= 2

            signal_type = "uint32_t"
            if max_value <= 256:
                signal_type = "uint8_t"
            elif max_value <= 65536:
                signal_type = "uint16_t"

            # If the signal is signed, or the offset is negative, remove "u" to use "int" type.
            if signal.is_signed or signal.offset < 0:
                signal_type = signal_type[1:]
        else:
            signal_type = "float"

        return signal_type

    def _is_signal_an_enum(self, signal):
        return signal.choices is not None

    def _get_sender(self, message):
        sender = "None"
        if len(message.senders) > 0:
            sender = message.senders[0]
        return sender

    def _message_is_relevant(self, message):
        return (self._get_sender(message).upper() == self._dbc_node_name.upper()) or (GENERATE_ALL_NODE_NAME == self._dbc_node_name.upper())

    # returns True if signal is little endian
    def _is_signal_little_endian(self, signal):
        return 'little' in signal.byte_order

    """
    Accessors
    """

    @property
    def dbc_filepath(self):
        return self._dbc_filepath

    @property
    def dbc_node_name(self):
        return self._dbc_node_name

    @property
    def valid_node_names(self):
        return self._valid_node_names
