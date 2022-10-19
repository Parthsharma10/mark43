// clang-format off
// AUTO-GENERATED - DO NOT EDIT
// Generated from test.dbc
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifndef MIN_OF
#define MIN_OF(x,y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX_OF
#define MAX_OF(x,y) ((x) > (y) ? (x) : (y))
#endif

/**
 * Extern dependency to use dbc_encode_and_send_*() API
 * This is designed such that the generated code does not depend on your CAN driver
 * @param argument_from_dbc_encode_and_send is a pass through argument from dbc_encode_and_send_*()
 * @returns the value returned from is returned from dbc_encode_and_send_*()
 */
extern bool dbc_send_can_message(void * argument_from_dbc_encode_and_send, uint32_t message_id, const uint8_t bytes[8], uint8_t dlc);

/// Missing in Action (MIA) structure
typedef struct {
  uint32_t mia_counter; ///< Counter used to track MIA
} dbc_mia_info_t;

/**
 * dbc_encode_*() API returns this instance to indicate message ID and DLC that should be used
 * dbc_decode_*() API checks against the provided header to make sure we are decoding the right message
 */
typedef struct {
  uint32_t message_id;  ///< CAN bus message identification
  uint8_t message_dlc;  ///< Data Length Code of the CAN message
} dbc_message_header_t;

// Enumeration for DBC_TEST1_enum
typedef enum {
  DBC_TEST1_enum__val_two = 2,
  DBC_TEST1_enum__val_one = 1,
  DBC_TEST1_enum__value_wierd_just_for_test_ = 0,
} DBC_TEST1_enum_e;

// Enumeration for DRIVER_HEARTBEAT_cmd
typedef enum {
  DRIVER_HEARTBEAT_cmd__REBOOT = 2,
  DRIVER_HEARTBEAT_cmd__SYNC = 1,
  DRIVER_HEARTBEAT_cmd__NOOP = 0,
} DRIVER_HEARTBEAT_cmd_e;

// Message headers containing CAN message IDs and their DLCs; @see dbc_message_header_t
static const dbc_message_header_t dbc_header_DBC_TEST0_FLOATS                    = {      100U, 6 };
static const dbc_message_header_t dbc_header_DBC_TEST1                           = {      200U, 4 };
static const dbc_message_header_t dbc_header_DBC_TEST2                           = {      300U, 7 };
static const dbc_message_header_t dbc_header_DBC_TEST3                           = {      400U, 2 };
static const dbc_message_header_t dbc_header_DRIVER_HEARTBEAT                    = {      500U, 1 };
static const dbc_message_header_t dbc_header_MOTOR_CMD                           = {      600U, 1 };
static const dbc_message_header_t dbc_header_MOTOR_STATUS                        = {      700U, 3 };
static const dbc_message_header_t dbc_header_SENSOR_SONARS                       = {      800U, 8 };
static const dbc_message_header_t dbc_header_DBC_TEST4                           = {      900U, 8 };
static const dbc_message_header_t dbc_header_DBC_TEST5                           = {     1000U, 2 };
static const dbc_message_header_t dbc_header_DBC_TEST6                           = {     1100U, 2 };
static const dbc_message_header_t dbc_header_DBC_TEST_BIG_ENDIAN                 = {     1200U, 6 };
static const dbc_message_header_t dbc_header_DBC_TEST_MIXED_ENDIAN               = {     1300U, 6 };

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST0_FLOATS */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST0_float
       +---+---+---+---+---+---+---+---+
     1 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     2 |<------------------------------|
 B     +---+---+---+---+---+---+---+---+
 y       +-- DBC_TEST0_float_signed_with_offset
 t     +---+---+---+---+---+---+---+---+
 e   3 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     4 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST0_float_signed
       +---+---+---+---+---+---+---+---+
     5 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST0_float_signed_min_max
#endif
/**
 * DBC_TEST0_FLOATS: Sent by 'IO'
 *   - Sync message used to synchronize the controllers
 *   - Expected every 10 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float DBC_TEST0_float;
  float DBC_TEST0_float_signed;
  float DBC_TEST0_float_signed_min_max;
  float DBC_TEST0_float_signed_with_offset;
} dbc_DBC_TEST0_FLOATS_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST1 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST1_unsigned
       +---+---+---+---+---+---+---+---+
     1 |<-----------------------------x|
 B     +---+---+---+---+---+---+---+---+
 y       +-- DBC_TEST1_unsigned_scaled
 t     +---+---+---+---+---+---+---+---+
 e   2 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST1_unsigned_minmax
       +---+---+---+---+---+---+---+---+
     3 |   |   |   |   |<-------------x|
       +---+---+---+---+---+---+---+---+
                         +-- DBC_TEST1_enum
#endif
/**
 * DBC_TEST1: Sent by 'IO'
 *   - Expected every 10 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  DBC_TEST1_enum_e DBC_TEST1_enum;
  uint16_t DBC_TEST1_unsigned_scaled;
  uint8_t DBC_TEST1_unsigned;
  uint8_t DBC_TEST1_unsigned_minmax;
} dbc_DBC_TEST1_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST2 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     1 |--------------x|<--------------|
       +---+---+---+---+---+---+---+---+
                         +-- DBC_TEST2_real_signed1
       +---+---+---+---+---+---+---+---+
     2 |-------------------------------|
       +---+---+---+---+---+---+---+---+
 B   3 |------x|<----------------------|
 y     +---+---+---+---+---+---+---+---+
 t               +-- DBC_TEST2_real_signed2
 e     +---+---+---+---+---+---+---+---+
     4 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST2_signed
       +---+---+---+---+---+---+---+---+
     5 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     6 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST2_signed_minmax
#endif
/**
 * DBC_TEST2: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  int16_t DBC_TEST2_real_signed1;
  int16_t DBC_TEST2_signed;
  int16_t DBC_TEST2_signed_minmax;
  int32_t DBC_TEST2_real_signed2;
} dbc_DBC_TEST2_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST3 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |   |   |<-------------x|   |   |
 B     +---+---+---+---+---+---+---+---+
 y               +-- DBC_TEST3_real_signed1
 t     +---+---+---+---+---+---+---+---+
 e   1 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST3_real_signed2
#endif
/**
 * DBC_TEST3: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  int16_t DBC_TEST3_real_signed2;
  int8_t DBC_TEST3_real_signed1;
} dbc_DBC_TEST3_s;

/* *********************************************************************************/
#if 0 /* Layout of DRIVER_HEARTBEAT */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
 B   0 |<-----------------------------x|
 y     +---+---+---+---+---+---+---+---+
 t       +-- DRIVER_HEARTBEAT_cmd
 e
#endif
/**
 * DRIVER_HEARTBEAT: Sent by 'DRIVER'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  DRIVER_HEARTBEAT_cmd_e DRIVER_HEARTBEAT_cmd;
} dbc_DRIVER_HEARTBEAT_s;

/* *********************************************************************************/
#if 0 /* Layout of MOTOR_CMD */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
 B   0 |<-------------x|<-------------x|
 y     +---+---+---+---+---+---+---+---+
 t       |               +-- MOTOR_CMD_steer
 e       +-- MOTOR_CMD_drive
#endif
/**
 * MOTOR_CMD: Sent by 'DRIVER'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  int8_t MOTOR_CMD_steer;
  uint8_t MOTOR_CMD_drive;
} dbc_MOTOR_CMD_s;

/* *********************************************************************************/
#if 0 /* Layout of MOTOR_STATUS */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |   |   |   |   |   |   |   |<-x|
       +---+---+---+---+---+---+---+---+
 B                                   +-- MOTOR_STATUS_wheel_error
 y     +---+---+---+---+---+---+---+---+
 t   1 |------------------------------x|
 e     +---+---+---+---+---+---+---+---+
     2 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- MOTOR_STATUS_speed_kph
#endif
/**
 * MOTOR_STATUS: Sent by 'MOTOR'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float MOTOR_STATUS_speed_kph; // unit: kph
  uint8_t MOTOR_STATUS_wheel_error;
} dbc_MOTOR_STATUS_s;

/* *********************************************************************************/
#if 0 /* Layout of SENSOR_SONARS */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |--------------x|<-------------x|
       +---+---+---+---+---+---+---+---+
                         +-- SENSOR_SONARS_mux
       +---+---+---+---+---+---+---+---+
     1 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- SENSOR_SONARS_err_count
       +---+---+---+---+---+---+---+---+
     2 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
       +---+---+---+---+---+---+---+---+
     3 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
       +---+---+---+---+---+---+---+---+
                         +-- SENSOR_SONARS_left
 B                       +-- SENSOR_SONARS_no_filt_left
 y     +---+---+---+---+---+---+---+---+
 t   4 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
 e     +---+---+---+---+---+---+---+---+
         +-- SENSOR_SONARS_middle
         +-- SENSOR_SONARS_no_filt_middle
       +---+---+---+---+---+---+---+---+
     5 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
       +---+---+---+---+---+---+---+---+
     6 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
       +---+---+---+---+---+---+---+---+
                         +-- SENSOR_SONARS_no_filt_right
                         +-- SENSOR_SONARS_right
       +---+---+---+---+---+---+---+---+
     7 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
       +---+---+---+---+---+---+---+---+
         +-- SENSOR_SONARS_no_filt_rear
         +-- SENSOR_SONARS_rear
#endif
/**
 * SENSOR_SONARS: Sent by 'SENSOR'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  uint8_t SENSOR_SONARS_mux; // Non-muxed signal
  uint16_t SENSOR_SONARS_err_count; // Non-muxed signal

  float SENSOR_SONARS_left; // M0
  float SENSOR_SONARS_middle; // M0
  float SENSOR_SONARS_right; // M0
  float SENSOR_SONARS_rear; // M0

  float SENSOR_SONARS_no_filt_left; // M1
  float SENSOR_SONARS_no_filt_middle; // M1
  float SENSOR_SONARS_no_filt_right; // M1
  float SENSOR_SONARS_no_filt_rear; // M1
} dbc_SENSOR_SONARS_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST4 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     1 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     2 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     3 |<------------------------------|
       +---+---+---+---+---+---+---+---+
 B       +-- DBC_TEST4_real_signed1
 y     +---+---+---+---+---+---+---+---+
 t   4 |------------------------------x|
 e     +---+---+---+---+---+---+---+---+
     5 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST4_real_signed2
       +---+---+---+---+---+---+---+---+
     6 |------------------------------x|
       +---+---+---+---+---+---+---+---+
     7 |<------------------------------|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST4_real_overflow
#endif
/**
 * DBC_TEST4: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  int32_t DBC_TEST4_real_signed1;
  int32_t DBC_TEST4_real_signed2;
  uint32_t DBC_TEST4_real_overflow;
} dbc_DBC_TEST4_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST5 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |----------x|<-----------------x|
 B     +---+---+---+---+---+---+---+---+
 y                   +-- DBC_TEST5_percent
 t     +---+---+---+---+---+---+---+---+
 e   1 |   |   |   |   |   |<----------|
       +---+---+---+---+---+---+---+---+
                             +-- DBC_TEST5_percent_float
#endif
/**
 * DBC_TEST5: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float DBC_TEST5_percent_float;
  uint8_t DBC_TEST5_percent;
} dbc_DBC_TEST5_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST6 */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |<-----------------------------x|
 B     +---+---+---+---+---+---+---+---+
 y       +-- DBC_TEST6_with_fractional_offset
 t     +---+---+---+---+---+---+---+---+
 e   1 |<-----------------------------x|
       +---+---+---+---+---+---+---+---+
         +-- DBC_TEST6_with_fractional_scale_offset
#endif
/**
 * DBC_TEST6: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float DBC_TEST6_with_fractional_offset;
  float DBC_TEST6_with_fractional_scale_offset;
} dbc_DBC_TEST6_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST_BIG_ENDIAN */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |   |   |   |<------------------|
       +---+---+---+---+---+---+---+---+
     1 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     2 |--------------------------x|   |
 B     +---+---+---+---+---+---+---+---+
 y                               +-- DBC_TEST_BIG_ENDIAN_SIG1
 t     +---+---+---+---+---+---+---+---+
 e   3 |   |   |   |<------------------|
       +---+---+---+---+---+---+---+---+
     4 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     5 |--------------------------x|   |
       +---+---+---+---+---+---+---+---+
                                 +-- DBC_TEST_BIG_ENDIAN_SIG2
#endif
/**
 * DBC_TEST_BIG_ENDIAN: Sent by 'IO'
 *   - Expected every 100 ms
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float DBC_TEST_BIG_ENDIAN_SIG2;
  uint32_t DBC_TEST_BIG_ENDIAN_SIG1;
} dbc_DBC_TEST_BIG_ENDIAN_s;

/* *********************************************************************************/
#if 0 /* Layout of DBC_TEST_MIXED_ENDIAN */
                      Bit

         7   6   5   4   3   2   1   0
       +---+---+---+---+---+---+---+---+
     0 |   |   |   |<------------------|
       +---+---+---+---+---+---+---+---+
     1 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     2 |----------x|   |   |   |   |   |
 B     +---+---+---+---+---+---+---+---+
 y               +-- DBC_TEST_MIXED_ENDIAN_SIG1
 t     +---+---+---+---+---+---+---+---+
 e   3 |------x|   |   |   |   |   |   |
       +---+---+---+---+---+---+---+---+
     4 |-------------------------------|
       +---+---+---+---+---+---+---+---+
     5 |   |   |<----------------------|
       +---+---+---+---+---+---+---+---+
                 +-- DBC_TEST_MIXED_ENDIAN_SIG2
#endif
/**
 * DBC_TEST_MIXED_ENDIAN: Sent by 'IO'
 */
typedef struct {
  dbc_mia_info_t mia_info;

  float DBC_TEST_MIXED_ENDIAN_SIG2;
  uint16_t DBC_TEST_MIXED_ENDIAN_SIG1;
} dbc_DBC_TEST_MIXED_ENDIAN_s;

/************************************************************************
 ********* Missing in Action (MIA) user dependencies
 ************************************************************************/


// -----------------------------------------------------------------------------
// When a message's MIA counter reaches this value
// corresponding MIA replacements occur
// -----------------------------------------------------------------------------
extern const uint32_t dbc_mia_threshold_DBC_TEST0_FLOATS;
extern const uint32_t dbc_mia_threshold_DBC_TEST1;
extern const uint32_t dbc_mia_threshold_DBC_TEST2;
extern const uint32_t dbc_mia_threshold_DBC_TEST3;
extern const uint32_t dbc_mia_threshold_DRIVER_HEARTBEAT;
extern const uint32_t dbc_mia_threshold_MOTOR_CMD;
extern const uint32_t dbc_mia_threshold_MOTOR_STATUS;
extern const uint32_t dbc_mia_threshold_SENSOR_SONARS;
extern const uint32_t dbc_mia_threshold_DBC_TEST4;
extern const uint32_t dbc_mia_threshold_DBC_TEST5;
extern const uint32_t dbc_mia_threshold_DBC_TEST6;
extern const uint32_t dbc_mia_threshold_DBC_TEST_BIG_ENDIAN;
extern const uint32_t dbc_mia_threshold_DBC_TEST_MIXED_ENDIAN;

// -----------------------------------------------------------------------------
// User must define these externed instances in their code to use MIA functions
// These are copied during dbc_service_mia_*() when message MIA timeout occurs
// -----------------------------------------------------------------------------
extern const dbc_DBC_TEST0_FLOATS_s     dbc_mia_replacement_DBC_TEST0_FLOATS; // Suggested MIA threshold: (3*10)
extern const dbc_DBC_TEST1_s            dbc_mia_replacement_DBC_TEST1; // Suggested MIA threshold: (3*10)
extern const dbc_DBC_TEST2_s            dbc_mia_replacement_DBC_TEST2; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST3_s            dbc_mia_replacement_DBC_TEST3; // Suggested MIA threshold: (3*100)
extern const dbc_DRIVER_HEARTBEAT_s     dbc_mia_replacement_DRIVER_HEARTBEAT; // Suggested MIA threshold: (3*100)
extern const dbc_MOTOR_CMD_s            dbc_mia_replacement_MOTOR_CMD; // Suggested MIA threshold: (3*100)
extern const dbc_MOTOR_STATUS_s         dbc_mia_replacement_MOTOR_STATUS; // Suggested MIA threshold: (3*100)
extern const dbc_SENSOR_SONARS_s        dbc_mia_replacement_SENSOR_SONARS; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST4_s            dbc_mia_replacement_DBC_TEST4; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST5_s            dbc_mia_replacement_DBC_TEST5; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST6_s            dbc_mia_replacement_DBC_TEST6; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST_BIG_ENDIAN_s  dbc_mia_replacement_DBC_TEST_BIG_ENDIAN; // Suggested MIA threshold: (3*100)
extern const dbc_DBC_TEST_MIXED_ENDIAN_s dbc_mia_replacement_DBC_TEST_MIXED_ENDIAN;

/************************************************************************
 ********* Encode methods
 ************************************************************************/

/**
 * Encode to transmit DBC_TEST0_FLOATS:
 *   Transmitter: 'IO' with message ID 100 composed of 6 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST0_FLOATS(uint8_t bytes[8], const dbc_DBC_TEST0_FLOATS_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 8-bit signal with scale=0.5
  raw = (uint64_t)((message->DBC_TEST0_float) / (float)0.5) & 0xff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  // Encode to raw 16-bit signal with scale=0.001 and offset=-32
  raw = (uint64_t)((message->DBC_TEST0_float_signed_with_offset - ((float)-32)) / (float)0.001) & 0xffff;
  bytes[1] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[2] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  // Encode to raw 16-bit SIGNED signal with scale=0.01
  raw = (uint64_t)((message->DBC_TEST0_float_signed) / (float)0.01) & 0xffff;
  bytes[3] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[4] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  // Encode to raw 8-bit SIGNED signal with scale=0.1 within range of [-12.8 -> 12.7]
  raw = (uint64_t)((MAX_OF(MIN_OF(message->DBC_TEST0_float_signed_min_max,(float)12.7),(float)-12.8)) / (float)0.1) & 0xff;
  bytes[5] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  return dbc_header_DBC_TEST0_FLOATS;
}

/// @see dbc_encode_DBC_TEST0_FLOATS(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST0_FLOATS(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST0_FLOATS_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST0_FLOATS(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST1:
 *   Transmitter: 'IO' with message ID 200 composed of 4 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST1(uint8_t bytes[8], const dbc_DBC_TEST1_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 8-bit signal with scale=1
  raw = (uint64_t)((message->DBC_TEST1_unsigned)) & 0xff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  // Encode to raw 8-bit signal with scale=10
  raw = (uint64_t)((message->DBC_TEST1_unsigned_scaled) / 10) & 0xff;
  bytes[1] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  // Encode to raw 8-bit signal with scale=1 within range of [0 -> 100]
  raw = (uint64_t)((MAX_OF(MIN_OF(message->DBC_TEST1_unsigned_minmax,100),0))) & 0xff;
  bytes[2] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  // Encode to raw 4-bit signal with scale=1
  raw = (uint64_t)((message->DBC_TEST1_enum)) & 0x0f;
  bytes[3] |= (((uint8_t)raw & 0x0f)); // write 4 bit(s) from bit position 0

  return dbc_header_DBC_TEST1;
}

/// @see dbc_encode_DBC_TEST1(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST1(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST1_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST1(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST2:
 *   Transmitter: 'IO' with message ID 300 composed of 7 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST2(uint8_t bytes[8], const dbc_DBC_TEST2_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 12-bit SIGNED signal with scale=1
  raw = (uint64_t)((message->DBC_TEST2_real_signed1)) & 0xfff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[1] |= (((uint8_t)(raw >> 8) & 0x0f)); // write 4 bit(s) from bit position 8

  // Encode to raw 18-bit SIGNED signal with scale=1
  raw = (uint64_t)((message->DBC_TEST2_real_signed2)) & 0x3ffff;
  bytes[1] |= (((uint8_t)raw & 0x0f) << 4); // write 4 bit(s) from bit position 0
  bytes[2] |= (((uint8_t)(raw >> 4) & 0xff)); // write 8 bit(s) from bit position 4
  bytes[3] |= (((uint8_t)(raw >> 12) & 0x3f)); // write 6 bit(s) from bit position 12

  // Encode to raw 10-bit signal with scale=1 and offset=-128
  raw = (uint64_t)(((int32_t)message->DBC_TEST2_signed - (-128))) & 0x3ff;
  bytes[3] |= (((uint8_t)raw & 0x03) << 6); // write 2 bit(s) from bit position 0
  bytes[4] |= (((uint8_t)(raw >> 2) & 0xff)); // write 8 bit(s) from bit position 2

  // Encode to raw 16-bit signal with scale=1 and offset=-32768 within range of [-32768 -> 32767]
  raw = (uint64_t)((MAX_OF(MIN_OF((int32_t)message->DBC_TEST2_signed_minmax,32767),-32768) - (-32768))) & 0xffff;
  bytes[5] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[6] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  return dbc_header_DBC_TEST2;
}

/// @see dbc_encode_DBC_TEST2(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST2(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST2_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST2(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST3:
 *   Transmitter: 'IO' with message ID 400 composed of 2 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST3(uint8_t bytes[8], const dbc_DBC_TEST3_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 4-bit signal with scale=1 and offset=-8
  raw = (uint64_t)(((int16_t)message->DBC_TEST3_real_signed1 - (-8))) & 0x0f;
  bytes[0] |= (((uint8_t)raw & 0x0f) << 2); // write 4 bit(s) from bit position 0

  // Encode to raw 8-bit SIGNED signal with scale=1 and offset=5
  raw = (uint64_t)(((int32_t)message->DBC_TEST3_real_signed2 - (5))) & 0xff;
  bytes[1] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  return dbc_header_DBC_TEST3;
}

/// @see dbc_encode_DBC_TEST3(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST3(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST3_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST3(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DRIVER_HEARTBEAT:
 *   Transmitter: 'DRIVER' with message ID 500 composed of 1 bytes
 */
static inline dbc_message_header_t dbc_encode_DRIVER_HEARTBEAT(uint8_t bytes[8], const dbc_DRIVER_HEARTBEAT_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 8-bit signal with scale=1
  raw = (uint64_t)((message->DRIVER_HEARTBEAT_cmd)) & 0xff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  return dbc_header_DRIVER_HEARTBEAT;
}

/// @see dbc_encode_DRIVER_HEARTBEAT(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DRIVER_HEARTBEAT(void *argument_for_dbc_send_can_message, const dbc_DRIVER_HEARTBEAT_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DRIVER_HEARTBEAT(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit MOTOR_CMD:
 *   Transmitter: 'DRIVER' with message ID 600 composed of 1 bytes
 */
static inline dbc_message_header_t dbc_encode_MOTOR_CMD(uint8_t bytes[8], const dbc_MOTOR_CMD_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 4-bit signal with scale=1 and offset=-5 within range of [-5 -> 5]
  raw = (uint64_t)((MAX_OF(MIN_OF((int16_t)message->MOTOR_CMD_steer,5),-5) - (-5))) & 0x0f;
  bytes[0] |= (((uint8_t)raw & 0x0f)); // write 4 bit(s) from bit position 0

  // Encode to raw 4-bit signal with scale=1 within range of [0 -> 9]
  raw = (uint64_t)((MAX_OF(MIN_OF(message->MOTOR_CMD_drive,9),0))) & 0x0f;
  bytes[0] |= (((uint8_t)raw & 0x0f) << 4); // write 4 bit(s) from bit position 0

  return dbc_header_MOTOR_CMD;
}

/// @see dbc_encode_MOTOR_CMD(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_MOTOR_CMD(void *argument_for_dbc_send_can_message, const dbc_MOTOR_CMD_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_MOTOR_CMD(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit MOTOR_STATUS:
 *   Transmitter: 'MOTOR' with message ID 700 composed of 3 bytes
 */
static inline dbc_message_header_t dbc_encode_MOTOR_STATUS(uint8_t bytes[8], const dbc_MOTOR_STATUS_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 1-bit signal with scale=1
  raw = (uint64_t)((message->MOTOR_STATUS_wheel_error)) & 0x01;
  bytes[0] |= (((uint8_t)raw & 0x01)); // write 1 bit(s) from bit position 0

  // Encode to raw 16-bit signal with scale=0.001
  raw = (uint64_t)((message->MOTOR_STATUS_speed_kph) / (float)0.001) & 0xffff;
  bytes[1] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[2] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  return dbc_header_MOTOR_STATUS;
}

/// @see dbc_encode_MOTOR_STATUS(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_MOTOR_STATUS(void *argument_for_dbc_send_can_message, const dbc_MOTOR_STATUS_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_MOTOR_STATUS(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit SENSOR_SONARS:
 *   Transmitter: 'SENSOR' with message ID 800 composed of 8 bytes
 */
static inline dbc_message_header_t dbc_encode_SENSOR_SONARS(uint8_t bytes[8], const dbc_SENSOR_SONARS_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Multiplexed signals are not handled yet

  return dbc_header_SENSOR_SONARS;
}

/// @see dbc_encode_SENSOR_SONARS(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_SENSOR_SONARS(void *argument_for_dbc_send_can_message, const dbc_SENSOR_SONARS_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_SENSOR_SONARS(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST4:
 *   Transmitter: 'IO' with message ID 900 composed of 8 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST4(uint8_t bytes[8], const dbc_DBC_TEST4_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 32-bit SIGNED signal with scale=1
  raw = (uint64_t)((message->DBC_TEST4_real_signed1)) & 0xffffffff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[1] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8
  bytes[2] |= (((uint8_t)(raw >> 16) & 0xff)); // write 8 bit(s) from bit position 16
  bytes[3] |= (((uint8_t)(raw >> 24) & 0xff)); // write 8 bit(s) from bit position 24

  // Encode to raw 16-bit SIGNED signal with scale=1 within range of [-32768 -> 32767]
  raw = (uint64_t)((MAX_OF(MIN_OF(message->DBC_TEST4_real_signed2,32767),-32768))) & 0xffff;
  bytes[4] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[5] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  // Encode to raw 16-bit signal with scale=10 and offset=100
  raw = (uint64_t)(((uint32_t)message->DBC_TEST4_real_overflow - (100)) / 10) & 0xffff;
  bytes[6] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0
  bytes[7] |= (((uint8_t)(raw >> 8) & 0xff)); // write 8 bit(s) from bit position 8

  return dbc_header_DBC_TEST4;
}

/// @see dbc_encode_DBC_TEST4(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST4(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST4_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST4(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST5:
 *   Transmitter: 'IO' with message ID 1000 composed of 2 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST5(uint8_t bytes[8], const dbc_DBC_TEST5_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 5-bit signal with scale=5
  raw = (uint64_t)((message->DBC_TEST5_percent) / 5) & 0x1f;
  bytes[0] |= (((uint8_t)raw & 0x1f)); // write 5 bit(s) from bit position 0

  // Encode to raw 6-bit signal with scale=2.5
  raw = (uint64_t)((message->DBC_TEST5_percent_float) / (float)2.5) & 0x3f;
  bytes[0] |= (((uint8_t)raw & 0x07) << 5); // write 3 bit(s) from bit position 0
  bytes[1] |= (((uint8_t)(raw >> 3) & 0x07)); // write 3 bit(s) from bit position 3

  return dbc_header_DBC_TEST5;
}

/// @see dbc_encode_DBC_TEST5(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST5(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST5_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST5(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST6:
 *   Transmitter: 'IO' with message ID 1100 composed of 2 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST6(uint8_t bytes[8], const dbc_DBC_TEST6_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 8-bit signal with scale=1 and offset=75.5
  raw = (uint64_t)(((uint16_t)message->DBC_TEST6_with_fractional_offset - ((float)75.5))) & 0xff;
  bytes[0] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  // Encode to raw 8-bit signal with scale=0.5 and offset=-75.5
  raw = (uint64_t)((message->DBC_TEST6_with_fractional_scale_offset - ((float)-75.5)) / (float)0.5) & 0xff;
  bytes[1] |= (((uint8_t)raw & 0xff)); // write 8 bit(s) from bit position 0

  return dbc_header_DBC_TEST6;
}

/// @see dbc_encode_DBC_TEST6(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST6(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST6_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST6(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST_BIG_ENDIAN:
 *   Transmitter: 'IO' with message ID 1200 composed of 6 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST_BIG_ENDIAN(uint8_t bytes[8], const dbc_DBC_TEST_BIG_ENDIAN_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 20-bit signal with scale=1
  raw = (uint64_t)((message->DBC_TEST_BIG_ENDIAN_SIG1)) & 0xfffff;
  // Note that this Big-Endian defines DBC bit 4, and actual signal starts at byte[2], bit(1)
  bytes[2] |= (((uint8_t)raw & 0x7f) << 1); // write 7 bit(s) from bit position 0
  bytes[1] |= (((uint8_t)(raw >> 7) & 0xff)); // write 8 bit(s) from bit position 7
  bytes[0] |= (((uint8_t)(raw >> 15) & 0x1f)); // write 5 bit(s) from bit position 15

  // Encode to raw 20-bit signal with scale=0.1
  raw = (uint64_t)((message->DBC_TEST_BIG_ENDIAN_SIG2) / (float)0.1) & 0xfffff;
  // Note that this Big-Endian defines DBC bit 28, and actual signal starts at byte[5], bit(1)
  bytes[5] |= (((uint8_t)raw & 0x7f) << 1); // write 7 bit(s) from bit position 0
  bytes[4] |= (((uint8_t)(raw >> 7) & 0xff)); // write 8 bit(s) from bit position 7
  bytes[3] |= (((uint8_t)(raw >> 15) & 0x1f)); // write 5 bit(s) from bit position 15

  return dbc_header_DBC_TEST_BIG_ENDIAN;
}

/// @see dbc_encode_DBC_TEST_BIG_ENDIAN(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST_BIG_ENDIAN(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST_BIG_ENDIAN_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST_BIG_ENDIAN(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/**
 * Encode to transmit DBC_TEST_MIXED_ENDIAN:
 *   Transmitter: 'IO' with message ID 1300 composed of 6 bytes
 */
static inline dbc_message_header_t dbc_encode_DBC_TEST_MIXED_ENDIAN(uint8_t bytes[8], const dbc_DBC_TEST_MIXED_ENDIAN_s *message) {
  uint64_t raw = 0;
  memset(bytes, 0, 8);

  // Encode to raw 16-bit signal with scale=1
  raw = (uint64_t)((message->DBC_TEST_MIXED_ENDIAN_SIG1)) & 0xffff;
  // Note that this Big-Endian defines DBC bit 4, and actual signal starts at byte[2], bit(5)
  bytes[2] |= (((uint8_t)raw & 0x07) << 5); // write 3 bit(s) from bit position 0
  bytes[1] |= (((uint8_t)(raw >> 3) & 0xff)); // write 8 bit(s) from bit position 3
  bytes[0] |= (((uint8_t)(raw >> 11) & 0x1f)); // write 5 bit(s) from bit position 11

  // Encode to raw 16-bit signal with scale=0.1
  raw = (uint64_t)((message->DBC_TEST_MIXED_ENDIAN_SIG2) / (float)0.1) & 0xffff;
  bytes[3] |= (((uint8_t)raw & 0x03) << 6); // write 2 bit(s) from bit position 0
  bytes[4] |= (((uint8_t)(raw >> 2) & 0xff)); // write 8 bit(s) from bit position 2
  bytes[5] |= (((uint8_t)(raw >> 10) & 0x3f)); // write 6 bit(s) from bit position 10

  return dbc_header_DBC_TEST_MIXED_ENDIAN;
}

/// @see dbc_encode_DBC_TEST_MIXED_ENDIAN(); this is its variant to encode and call dbc_send_can_message() to send the message
static inline bool dbc_encode_and_send_DBC_TEST_MIXED_ENDIAN(void *argument_for_dbc_send_can_message, const dbc_DBC_TEST_MIXED_ENDIAN_s *message) {
  uint8_t bytes[8];
  const dbc_message_header_t header = dbc_encode_DBC_TEST_MIXED_ENDIAN(bytes, message);
  return dbc_send_can_message(argument_for_dbc_send_can_message, header.message_id, bytes, header.message_dlc);
}

/************************************************************************
 ********* Decode methods
 ************************************************************************/

/**
 * Decode received message DBC_TEST0_FLOATS: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST0_FLOATS(dbc_DBC_TEST0_FLOATS_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST0_FLOATS.message_id) || (header.message_dlc != dbc_header_DBC_TEST0_FLOATS.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST0_float = ((raw * (float)0.5));

  raw = ((bytes[1])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[2])) << 8; // extract 8 bit(s) to bit position 8
  message->DBC_TEST0_float_signed_with_offset = ((raw * (float)0.001) + ((float)-32));

  raw = ((bytes[3])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[4])) << 8; // extract 8 bit(s) to bit position 8
  if (raw & (1 << 15)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST0_float_signed = ((int32_t)((~0U << 15) | raw) * (float)0.01);
  } else {
    message->DBC_TEST0_float_signed = ((raw * (float)0.01)); // Copy unsigned raw number
  }

  raw = ((bytes[5])); // extract 8 bit(s) to bit position 0
  if (raw & (1 << 7)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST0_float_signed_min_max = ((int32_t)((~0U << 7) | raw) * (float)0.1);
  } else {
    message->DBC_TEST0_float_signed_min_max = ((raw * (float)0.1)); // Copy unsigned raw number
  }

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST1: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST1(dbc_DBC_TEST1_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST1.message_id) || (header.message_dlc != dbc_header_DBC_TEST1.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST1_unsigned = raw;

  raw = ((bytes[1])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST1_unsigned_scaled = ((raw * 10));

  raw = ((bytes[2])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST1_unsigned_minmax = raw;

  raw = ((bytes[3]) & 0x0f); // extract 4 bit(s) to bit position 0
  message->DBC_TEST1_enum = (DBC_TEST1_enum_e)raw;

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST2: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST2(dbc_DBC_TEST2_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST2.message_id) || (header.message_dlc != dbc_header_DBC_TEST2.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[1]) & 0x0f) << 8; // extract 4 bit(s) to bit position 8
  if (raw & (1 << 11)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST2_real_signed1 = ((int32_t)((~0U << 11) | raw));
  } else {
    message->DBC_TEST2_real_signed1 = raw; // Copy unsigned raw number
  }

  raw = ((bytes[1] >> 4) & 0x0f); // extract 4 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[2])) << 4; // extract 8 bit(s) to bit position 4
  raw |= (uint64_t)((bytes[3]) & 0x3f) << 12; // extract 6 bit(s) to bit position 12
  if (raw & (1 << 17)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST2_real_signed2 = ((int32_t)((~0U << 17) | raw));
  } else {
    message->DBC_TEST2_real_signed2 = raw; // Copy unsigned raw number
  }

  raw = ((bytes[3] >> 6) & 0x03); // extract 2 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[4])) << 2; // extract 8 bit(s) to bit position 2
  message->DBC_TEST2_signed = (raw + (-128));

  raw = ((bytes[5])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[6])) << 8; // extract 8 bit(s) to bit position 8
  message->DBC_TEST2_signed_minmax = (raw + (-32768));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST3: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST3(dbc_DBC_TEST3_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST3.message_id) || (header.message_dlc != dbc_header_DBC_TEST3.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0] >> 2) & 0x0f); // extract 4 bit(s) to bit position 0
  message->DBC_TEST3_real_signed1 = (raw + (-8));

  raw = ((bytes[1])); // extract 8 bit(s) to bit position 0
  if (raw & (1 << 7)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST3_real_signed2 = ((int32_t)((~0U << 7) | raw)) + (5);
  } else {
    message->DBC_TEST3_real_signed2 = (raw + (5)); // Copy unsigned raw number
  }

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DRIVER_HEARTBEAT: Sent by DRIVER
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DRIVER_HEARTBEAT(dbc_DRIVER_HEARTBEAT_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DRIVER_HEARTBEAT.message_id) || (header.message_dlc != dbc_header_DRIVER_HEARTBEAT.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  message->DRIVER_HEARTBEAT_cmd = (DRIVER_HEARTBEAT_cmd_e)raw;

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message MOTOR_CMD: Sent by DRIVER
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_MOTOR_CMD(dbc_MOTOR_CMD_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_MOTOR_CMD.message_id) || (header.message_dlc != dbc_header_MOTOR_CMD.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0]) & 0x0f); // extract 4 bit(s) to bit position 0
  message->MOTOR_CMD_steer = (raw + (-5));

  raw = ((bytes[0] >> 4) & 0x0f); // extract 4 bit(s) to bit position 0
  message->MOTOR_CMD_drive = raw;

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message MOTOR_STATUS: Sent by MOTOR
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_MOTOR_STATUS(dbc_MOTOR_STATUS_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_MOTOR_STATUS.message_id) || (header.message_dlc != dbc_header_MOTOR_STATUS.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0]) & 0x01); // extract 1 bit(s) to bit position 0
  message->MOTOR_STATUS_wheel_error = raw;

  raw = ((bytes[1])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[2])) << 8; // extract 8 bit(s) to bit position 8
  message->MOTOR_STATUS_speed_kph = ((raw * (float)0.001));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message SENSOR_SONARS: Sent by SENSOR
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_SENSOR_SONARS(dbc_SENSOR_SONARS_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_SENSOR_SONARS.message_id) || (header.message_dlc != dbc_header_SENSOR_SONARS.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  // Multiplexed signals are not handled yet
  (void)raw;

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST4: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST4(dbc_DBC_TEST4_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST4.message_id) || (header.message_dlc != dbc_header_DBC_TEST4.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[1])) << 8; // extract 8 bit(s) to bit position 8
  raw |= (uint64_t)((bytes[2])) << 16; // extract 8 bit(s) to bit position 16
  raw |= (uint64_t)((bytes[3])) << 24; // extract 8 bit(s) to bit position 24
  if (raw & (1 << 31)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST4_real_signed1 = ((int32_t)((~0U << 31) | raw));
  } else {
    message->DBC_TEST4_real_signed1 = raw; // Copy unsigned raw number
  }

  raw = ((bytes[4])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[5])) << 8; // extract 8 bit(s) to bit position 8
  if (raw & (1 << 15)) { // Check signed bit of the raw DBC signal and sign extend from 'raw'
    message->DBC_TEST4_real_signed2 = ((int32_t)((~0U << 15) | raw));
  } else {
    message->DBC_TEST4_real_signed2 = raw; // Copy unsigned raw number
  }

  raw = ((bytes[6])); // extract 8 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[7])) << 8; // extract 8 bit(s) to bit position 8
  message->DBC_TEST4_real_overflow = ((raw * 10) + (100));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST5: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST5(dbc_DBC_TEST5_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST5.message_id) || (header.message_dlc != dbc_header_DBC_TEST5.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0]) & 0x1f); // extract 5 bit(s) to bit position 0
  message->DBC_TEST5_percent = ((raw * 5));

  raw = ((bytes[0] >> 5) & 0x07); // extract 3 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[1]) & 0x07) << 3; // extract 3 bit(s) to bit position 3
  message->DBC_TEST5_percent_float = ((raw * (float)2.5));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST6: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST6(dbc_DBC_TEST6_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST6.message_id) || (header.message_dlc != dbc_header_DBC_TEST6.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  raw = ((bytes[0])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST6_with_fractional_offset = (raw + ((float)75.5));

  raw = ((bytes[1])); // extract 8 bit(s) to bit position 0
  message->DBC_TEST6_with_fractional_scale_offset = ((raw * (float)0.5) + ((float)-75.5));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST_BIG_ENDIAN: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST_BIG_ENDIAN(dbc_DBC_TEST_BIG_ENDIAN_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST_BIG_ENDIAN.message_id) || (header.message_dlc != dbc_header_DBC_TEST_BIG_ENDIAN.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  // Note that this Big-Endian defines DBC bit 4, and actual signal starts at byte[2], bit(1)
  raw = ((bytes[2] >> 1) & 0x7f); // extract 7 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[1])) << 7; // extract 8 bit(s) to bit position 7
  raw |= (uint64_t)((bytes[0]) & 0x1f) << 15; // extract 5 bit(s) to bit position 15
  message->DBC_TEST_BIG_ENDIAN_SIG1 = raw;

  // Note that this Big-Endian defines DBC bit 28, and actual signal starts at byte[5], bit(1)
  raw = ((bytes[5] >> 1) & 0x7f); // extract 7 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[4])) << 7; // extract 8 bit(s) to bit position 7
  raw |= (uint64_t)((bytes[3]) & 0x1f) << 15; // extract 5 bit(s) to bit position 15
  message->DBC_TEST_BIG_ENDIAN_SIG2 = ((raw * (float)0.1));

  message->mia_info.mia_counter = 0;
  return success;
}
/**
 * Decode received message DBC_TEST_MIXED_ENDIAN: Sent by IO
 *   Provided a dbc_message_header_t, this will attempt to decode the received message and return true upon success
 */
static inline bool dbc_decode_DBC_TEST_MIXED_ENDIAN(dbc_DBC_TEST_MIXED_ENDIAN_s *message, const dbc_message_header_t header, const uint8_t bytes[8]) {
  const bool success = true;
  if ((header.message_id != dbc_header_DBC_TEST_MIXED_ENDIAN.message_id) || (header.message_dlc != dbc_header_DBC_TEST_MIXED_ENDIAN.message_dlc)) {
    return !success;
  }

  uint64_t raw = 0;
  // Note that this Big-Endian defines DBC bit 4, and actual signal starts at byte[2], bit(5)
  raw = ((bytes[2] >> 5) & 0x07); // extract 3 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[1])) << 3; // extract 8 bit(s) to bit position 3
  raw |= (uint64_t)((bytes[0]) & 0x1f) << 11; // extract 5 bit(s) to bit position 11
  message->DBC_TEST_MIXED_ENDIAN_SIG1 = raw;

  raw = ((bytes[3] >> 6) & 0x03); // extract 2 bit(s) to bit position 0
  raw |= (uint64_t)((bytes[4])) << 2; // extract 8 bit(s) to bit position 2
  raw |= (uint64_t)((bytes[5]) & 0x3f) << 10; // extract 6 bit(s) to bit position 10
  message->DBC_TEST_MIXED_ENDIAN_SIG2 = ((raw * (float)0.1));

  message->mia_info.mia_counter = 0;
  return success;
}

/************************************************************************
 ********* MIA methods
 ************************************************************************/

// Do not use this function
static inline bool dbc_service_mia_for(dbc_mia_info_t *mia_info, const uint32_t increment_mia_by, const uint32_t threshold) {
  bool message_just_entered_mia = false;

  if (mia_info->mia_counter >= threshold) {
    // Message is already MIA
  } else {
    mia_info->mia_counter += increment_mia_by;
    message_just_entered_mia = (mia_info->mia_counter >= threshold);
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST0_FLOATS(dbc_DBC_TEST0_FLOATS_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST0_FLOATS);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST0_FLOATS;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST1(dbc_DBC_TEST1_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST1);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST1;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST2(dbc_DBC_TEST2_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST2);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST2;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST3(dbc_DBC_TEST3_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST3);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST3;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DRIVER_HEARTBEAT(dbc_DRIVER_HEARTBEAT_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DRIVER_HEARTBEAT);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DRIVER_HEARTBEAT;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_MOTOR_CMD(dbc_MOTOR_CMD_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_MOTOR_CMD);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_MOTOR_CMD;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_MOTOR_STATUS(dbc_MOTOR_STATUS_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_MOTOR_STATUS);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_MOTOR_STATUS;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_SENSOR_SONARS(dbc_SENSOR_SONARS_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_SENSOR_SONARS);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_SENSOR_SONARS;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST4(dbc_DBC_TEST4_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST4);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST4;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST5(dbc_DBC_TEST5_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST5);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST5;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST6(dbc_DBC_TEST6_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST6);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST6;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST_BIG_ENDIAN(dbc_DBC_TEST_BIG_ENDIAN_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST_BIG_ENDIAN);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST_BIG_ENDIAN;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

static inline bool dbc_service_mia_DBC_TEST_MIXED_ENDIAN(dbc_DBC_TEST_MIXED_ENDIAN_s *message, const uint32_t increment_mia_by) {
  const bool message_just_entered_mia = dbc_service_mia_for(&(message->mia_info), increment_mia_by, dbc_mia_threshold_DBC_TEST_MIXED_ENDIAN);

  if (message_just_entered_mia) {
    const dbc_mia_info_t previous_mia = message->mia_info;
    *message = dbc_mia_replacement_DBC_TEST_MIXED_ENDIAN;
    message->mia_info = previous_mia;
  }

  return message_just_entered_mia;
}

// clang-format off
