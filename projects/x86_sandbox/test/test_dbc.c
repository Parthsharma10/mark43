#include "unity.h"

#include "dbc.h"

const uint32_t dbc_mia_threshold_DBC_TEST1 = 100;
const uint32_t dbc_mia_threshold_DBC_TEST2 = 100;
const uint32_t dbc_mia_threshold_DBC_TEST3 = 100;
const uint32_t dbc_mia_threshold_DRIVER_HEARTBEAT = 100;
const uint32_t dbc_mia_threshold_MOTOR_CMD = 100;
const uint32_t dbc_mia_threshold_MOTOR_STATUS = 100;
const uint32_t dbc_mia_threshold_SENSOR_SONARS = 100;
const uint32_t dbc_mia_threshold_DBC_TEST4 = 100;

const dbc_DBC_TEST1_s dbc_mia_replacement_DBC_TEST1;
const dbc_DBC_TEST2_s dbc_mia_replacement_DBC_TEST2;
const dbc_DBC_TEST3_s dbc_mia_replacement_DBC_TEST3;
const dbc_DRIVER_HEARTBEAT_s dbc_mia_replacement_DRIVER_HEARTBEAT;
const dbc_MOTOR_CMD_s dbc_mia_replacement_MOTOR_CMD;
const dbc_MOTOR_STATUS_s dbc_mia_replacement_MOTOR_STATUS;
const dbc_SENSOR_SONARS_s dbc_mia_replacement_SENSOR_SONARS;
const dbc_DBC_TEST4_s dbc_mia_replacement_DBC_TEST4;

static uint8_t bytes[8] = {0};

void setUp() { memset(bytes, 0, sizeof(bytes)); }

void test_encode_decode__dbc_DBC_TEST1_s__basic() {
  const dbc_DBC_TEST1_s msg = {};

  const dbc_message_header_t header = dbc_encode_DBC_TEST1(bytes, &msg);
  TEST_ASSERT_EQUAL(200, header.message_id);
  TEST_ASSERT_EQUAL(4, header.message_dlc);
}

void test_encode_decode__dbc_DBC_TEST1_s__bad_header() {
  dbc_DBC_TEST1_s decoded = {0};
  const dbc_message_header_t bad_header;
  TEST_ASSERT_FALSE(dbc_decode_DBC_TEST1(&decoded, bad_header, bytes));
}

void test_encode_decode__dbc_DBC_TEST0_FLOATS__unsigned() {
  dbc_DBC_TEST0_FLOATS_s msg = {};
  dbc_DBC_TEST0_FLOATS_s decoded = {};

  msg.DBC_TEST0_float = 100.5;
  msg.DBC_TEST0_float_signed_with_offset = +32.123;
  msg.DBC_TEST0_float_signed =
      +312.123; // aim towards high number we can acheive based on the DBC: `8|16@1+ (0.001,-32)`
  msg.DBC_TEST0_float_signed_min_max = +12.7; // DBC: `40|8@1- (0.1,0)`

  const dbc_message_header_t header = dbc_encode_DBC_TEST0_FLOATS(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST0_FLOATS(&decoded, header, bytes));
  TEST_ASSERT_FLOAT_WITHIN(0.5, msg.DBC_TEST0_float, decoded.DBC_TEST0_float);
  TEST_ASSERT_FLOAT_WITHIN(0.001, msg.DBC_TEST0_float_signed_with_offset, decoded.DBC_TEST0_float_signed_with_offset);
  TEST_ASSERT_FLOAT_WITHIN(0.01, msg.DBC_TEST0_float_signed, decoded.DBC_TEST0_float_signed);
  TEST_ASSERT_FLOAT_WITHIN(0.1, msg.DBC_TEST0_float_signed_min_max, decoded.DBC_TEST0_float_signed_min_max);
}

void test_encode_decode__dbc_DBC_TEST0_FLOATS__signed() {
  dbc_DBC_TEST0_FLOATS_s msg = {};
  dbc_DBC_TEST0_FLOATS_s decoded = {};

  msg.DBC_TEST0_float = 1.5;
  msg.DBC_TEST0_float_signed_with_offset = -29.123;
  msg.DBC_TEST0_float_signed = -123.4; // aim towards high number we can acheive based on the DBC: `8|16@1+ (0.001,-32)`
  msg.DBC_TEST0_float_signed_min_max = -12.5; // DBC: `40|8@1- (0.1,-2)`

  const dbc_message_header_t header = dbc_encode_DBC_TEST0_FLOATS(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST0_FLOATS(&decoded, header, bytes));
  TEST_ASSERT_FLOAT_WITHIN(0.5, msg.DBC_TEST0_float, decoded.DBC_TEST0_float);
  TEST_ASSERT_FLOAT_WITHIN(0.001, msg.DBC_TEST0_float_signed_with_offset, decoded.DBC_TEST0_float_signed_with_offset);
  TEST_ASSERT_FLOAT_WITHIN(0.01, msg.DBC_TEST0_float_signed, decoded.DBC_TEST0_float_signed);
  TEST_ASSERT_FLOAT_WITHIN(0.1, msg.DBC_TEST0_float_signed_min_max, decoded.DBC_TEST0_float_signed_min_max);
}

void test_encode_decode__dbc_DBC_TEST1_s() {
  dbc_DBC_TEST1_s msg = {};
  dbc_DBC_TEST1_s decoded = {};

  msg.DBC_TEST1_enum = DBC_TEST1_enum__val_one;
  msg.DBC_TEST1_unsigned = 255;
  msg.DBC_TEST1_unsigned_minmax = 34;

  const dbc_message_header_t header = dbc_encode_DBC_TEST1(bytes, &msg);

  // Validate decoded signals
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST1(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(DBC_TEST1_enum__val_one, decoded.DBC_TEST1_enum);
  TEST_ASSERT_EQUAL(msg.DBC_TEST1_unsigned, decoded.DBC_TEST1_unsigned);
  TEST_ASSERT_EQUAL(msg.DBC_TEST1_unsigned_minmax, decoded.DBC_TEST1_unsigned_minmax);
}

void test_encode_decode__dbc_DBC_TEST2_s() {
  dbc_DBC_TEST2_s decoded = {};
  dbc_DBC_TEST2_s msg = {};

  msg.DBC_TEST2_real_signed1 = -100;
  msg.DBC_TEST2_real_signed2 = +100;
  msg.DBC_TEST2_signed = -128;
  msg.DBC_TEST2_signed_minmax = 10000;

  const dbc_message_header_t header = dbc_encode_DBC_TEST2(bytes, &msg);

  // Validate decoded signals
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST2(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(msg.DBC_TEST2_real_signed1, decoded.DBC_TEST2_real_signed1);
  TEST_ASSERT_EQUAL(msg.DBC_TEST2_real_signed2, decoded.DBC_TEST2_real_signed2);
  TEST_ASSERT_EQUAL(msg.DBC_TEST2_signed, decoded.DBC_TEST2_signed);
  TEST_ASSERT_EQUAL(msg.DBC_TEST2_signed_minmax, decoded.DBC_TEST2_signed_minmax);

  msg.DBC_TEST2_signed_minmax = -10000;
  dbc_encode_DBC_TEST2(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST2(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(msg.DBC_TEST2_signed_minmax, decoded.DBC_TEST2_signed_minmax);
}

void test_encode_decode__dbc_DBC_TEST4_s() {
  dbc_DBC_TEST4_s decoded = {};
  dbc_DBC_TEST4_s msg = {};

  msg.DBC_TEST4_real_signed1 = -INT32_MAX;
  msg.DBC_TEST4_real_signed2 = (UINT16_MAX / 2) - 1;
  msg.DBC_TEST4_real_overflow = 10 * 1000;

  const dbc_message_header_t header = dbc_encode_DBC_TEST4(bytes, &msg);

  // Validate decoded signals
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST4(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(msg.DBC_TEST4_real_signed1, decoded.DBC_TEST4_real_signed1);
  TEST_ASSERT_EQUAL(msg.DBC_TEST4_real_signed2, decoded.DBC_TEST4_real_signed2);
  TEST_ASSERT_EQUAL(msg.DBC_TEST4_real_overflow, decoded.DBC_TEST4_real_overflow);
}

void test_encode_decode__dbc_DBC_TEST5_s() {
  dbc_DBC_TEST5_s decoded = {};
  dbc_DBC_TEST5_s msg = {};

  const uint32_t expected_percentage = 90; // gets rounded down due to scale of (5,0)
  msg.DBC_TEST5_percent = 92;
  msg.DBC_TEST5_percent_float = 50.5;

  const dbc_message_header_t header = dbc_encode_DBC_TEST5(bytes, &msg);

  // Validate decoded signals
  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST5(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(expected_percentage, decoded.DBC_TEST5_percent);
  TEST_ASSERT_EQUAL(msg.DBC_TEST5_percent_float, decoded.DBC_TEST5_percent_float);
}

void test_encode_decode__dbc_encode_MOTOR_CMD() {
  dbc_MOTOR_CMD_s decoded = {};
  dbc_MOTOR_CMD_s msg = {};

  // min values
  msg.MOTOR_CMD_drive = 0;
  msg.MOTOR_CMD_steer = -5;
  const dbc_message_header_t header = dbc_encode_MOTOR_CMD(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_MOTOR_CMD(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(0, msg.MOTOR_CMD_drive);
  TEST_ASSERT_EQUAL(-5, msg.MOTOR_CMD_steer);

  // max values
  msg.MOTOR_CMD_drive = 9;
  msg.MOTOR_CMD_steer = +5;
  dbc_encode_MOTOR_CMD(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_MOTOR_CMD(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(9, decoded.MOTOR_CMD_drive);
  TEST_ASSERT_EQUAL(+5, decoded.MOTOR_CMD_steer);

  // out of bounds on negative
  msg.MOTOR_CMD_drive = 0;
  msg.MOTOR_CMD_steer = -60;
  dbc_encode_MOTOR_CMD(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_MOTOR_CMD(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(-0, decoded.MOTOR_CMD_drive);
  TEST_ASSERT_EQUAL(-5, decoded.MOTOR_CMD_steer);

  // out of bounds on positive
  msg.MOTOR_CMD_drive = 100;
  msg.MOTOR_CMD_steer = 6;
  dbc_encode_MOTOR_CMD(bytes, &msg);
  TEST_ASSERT_TRUE(dbc_decode_MOTOR_CMD(&decoded, header, bytes));
  TEST_ASSERT_EQUAL(9, decoded.MOTOR_CMD_drive);
  TEST_ASSERT_EQUAL(5, decoded.MOTOR_CMD_steer);
}

void test_encode_decode__big_endian(void) {
  dbc_DBC_TEST_BIG_ENDIAN_s encoded = {};
  dbc_DBC_TEST_BIG_ENDIAN_s decoded = {};
  uint8_t encoded_bytes[8] = {0};

  encoded.DBC_TEST_BIG_ENDIAN_SIG1 = 0x1122;
  encoded.DBC_TEST_BIG_ENDIAN_SIG2 = 0xABCDE;
  const dbc_message_header_t header = dbc_encode_DBC_TEST_BIG_ENDIAN(encoded_bytes, &encoded);

  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST_BIG_ENDIAN(&decoded, header, encoded_bytes));
  TEST_ASSERT_EQUAL(encoded.DBC_TEST_BIG_ENDIAN_SIG1, decoded.DBC_TEST_BIG_ENDIAN_SIG1);
  TEST_ASSERT_EQUAL(encoded.DBC_TEST_BIG_ENDIAN_SIG1, decoded.DBC_TEST_BIG_ENDIAN_SIG1);
}

void test_encode_decode__mixed_endian(void) {
  dbc_DBC_TEST_MIXED_ENDIAN_s encoded = {};
  dbc_DBC_TEST_MIXED_ENDIAN_s decoded = {};
  uint8_t encoded_bytes[8] = {0};

  encoded.DBC_TEST_MIXED_ENDIAN_SIG1 = 0x1122;
  encoded.DBC_TEST_MIXED_ENDIAN_SIG2 = 0xABCDE;
  const dbc_message_header_t header = dbc_encode_DBC_TEST_MIXED_ENDIAN(encoded_bytes, &encoded);

  TEST_ASSERT_TRUE(dbc_decode_DBC_TEST_MIXED_ENDIAN(&decoded, header, encoded_bytes));
  TEST_ASSERT_EQUAL(encoded.DBC_TEST_MIXED_ENDIAN_SIG1, decoded.DBC_TEST_MIXED_ENDIAN_SIG1);
  TEST_ASSERT_EQUAL(encoded.DBC_TEST_MIXED_ENDIAN_SIG1, decoded.DBC_TEST_MIXED_ENDIAN_SIG1);
}

void test_mia_counter(void) {
  dbc_MOTOR_STATUS_s msg = {};
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 10));
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 40));
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 40));

  TEST_ASSERT_TRUE(dbc_service_mia_MOTOR_STATUS(&msg, 10));

  // Should remain MIA
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 10));
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 10));
}

void test_mia_replacement(void) {
  dbc_MOTOR_STATUS_s msg = {};
  msg.MOTOR_STATUS_speed_kph = 10;
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 90));

  TEST_ASSERT_EQUAL(10, msg.MOTOR_STATUS_speed_kph);
  TEST_ASSERT_TRUE(dbc_service_mia_MOTOR_STATUS(&msg, 10));
  TEST_ASSERT_EQUAL(0, msg.MOTOR_STATUS_speed_kph);

  // already MIA so should not be changed
  msg.MOTOR_STATUS_speed_kph = 20;
  TEST_ASSERT_FALSE(dbc_service_mia_MOTOR_STATUS(&msg, 10));
  TEST_ASSERT_EQUAL(20, msg.MOTOR_STATUS_speed_kph);
}

bool dbc_send_can_message(void *argument, uint32_t message_id, const uint8_t bytes[8], uint8_t dlc) {
  TEST_ASSERT_EQUAL(dbc_header_MOTOR_STATUS.message_id, message_id);
  TEST_ASSERT_EQUAL(dbc_header_MOTOR_STATUS.message_dlc, dlc);
  TEST_ASSERT_EQUAL((void *)0xDEADBEEF, argument);
  return true;
}

void test_encode_and_send(void) {
  dbc_MOTOR_STATUS_s msg = {};
  TEST_ASSERT_TRUE(dbc_encode_and_send_MOTOR_STATUS((void *)0xDEADBEEF, &msg));
}