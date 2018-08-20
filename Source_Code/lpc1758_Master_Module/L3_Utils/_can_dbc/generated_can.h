/// DBC file: ../../alpha_dbc.dbc    Self node: 'DRIVER'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

static const dbc_msg_hdr_t INITIAL_END_HDR =                      {  100, 1 };
static const dbc_msg_hdr_t GPS_DESTINATION_HDR =                  {  101, 8 };
static const dbc_msg_hdr_t MOTOR_SIGNAL_HDR =                     {  300, 3 };
static const dbc_msg_hdr_t SENSOR_SONARS_HDR =                    {  200, 8 };
// static const dbc_msg_hdr_t CURRENT_HDR =                          {  550, 8 };




/// Message: INITIAL_END from 'BRIDGE', DLC: 1 byte(s), MID: 100
typedef struct {
    uint8_t FLAG : 1;                         ///< B0:0   Destination: DRIVER

    dbc_mia_info_t mia_info;
} INITIAL_END_t;


/// Message: GPS_DESTINATION from 'BRIDGE', DLC: 8 byte(s), MID: 101
typedef struct {
    float GPS_DESTINATION_latitude;           ///< B31:0   Destination: DRIVER
    float GPS_DESTINATION_longitude;          ///< B63:32   Destination: DRIVER

    dbc_mia_info_t mia_info;
} GPS_DESTINATION_t;


/// Message: MOTOR_SIGNAL from 'DRIVER', DLC: 3 byte(s), MID: 300
typedef struct {
    uint8_t MOTOR_STEER_FULL_LEFT : 1;        ///< B0:0   Destination: MOTOR
    uint8_t MOTOR_STEER_SLIGHT_LEFT : 1;      ///< B1:1   Destination: MOTOR
    uint8_t MOTOR_STEER_FULL_RIGHT : 1;       ///< B2:2   Destination: MOTOR
    uint8_t MOTOR_STEER_SLIGHT_RIGHT : 1;     ///< B3:3   Destination: MOTOR
    uint8_t MOTOR_STEER_STRAIGHT : 1;         ///< B4:4   Destination: MOTOR
    uint8_t MOTOR_DRIVE_FORWARD : 1;          ///< B5:5   Destination: MOTOR
    uint8_t MOTOR_DRIVE_REVERSE : 1;          ///< B6:6   Destination: MOTOR
    uint8_t MOTOR_DRIVE_NEUTRAL : 1;          ///< B7:7   Destination: MOTOR
    uint8_t MOTOR_DRIVE_SPEED;                ///< B13:8  Min: 0 Max: 60   Destination: MOTOR
    uint8_t MOTOR_STEER_ANGLE;                ///< B20:14  Min: 10 Max: 20   Destination: MOTOR
    uint8_t MOTOR_DRIVE_STOP : 1;             ///< B21:21  Min: 0 Max: 1   Destination: MOTOR

    // No dbc_mia_info_t for a message that we will send
} MOTOR_SIGNAL_t;


/// Message: SENSOR_SONARS from 'SENSOR', DLC: 8 byte(s), MID: 200
typedef struct {
    uint16_t SENSOR_SONARS_left;              ///< B15:0  Min: 0 Max: 256   Destination: DRIVER,IO
    uint16_t SENSOR_SONARS_middle;            ///< B31:16  Min: 0 Max: 256   Destination: DRIVER,IO
    uint16_t SENSOR_SONARS_right;             ///< B47:32  Min: 0 Max: 256   Destination: DRIVER,IO
    uint16_t SENSOR_SONARS_rear;              ///< B63:48  Min: 0 Max: 256   Destination: DRIVER,IO

    dbc_mia_info_t mia_info;
} SENSOR_SONARS_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             INITIAL_END__MIA_MS;
extern const INITIAL_END_t                        INITIAL_END__MIA_MSG;
extern const uint32_t                             GPS_DESTINATION__MIA_MS;
extern const GPS_DESTINATION_t                    GPS_DESTINATION__MIA_MSG;
extern const uint32_t                             SENSOR_SONARS__MIA_MS;
extern const SENSOR_SONARS_t                      SENSOR_SONARS__MIA_MSG;
/// @}


/// Not generating code for dbc_encode_INITIAL_END() since the sender is BRIDGE and we are DRIVER

/// Not generating code for dbc_encode_GPS_DESTINATION() since the sender is BRIDGE and we are DRIVER

/// Encode DRIVER's 'MOTOR_SIGNAL' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_MOTOR_SIGNAL(uint8_t bytes[8], MOTOR_SIGNAL_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->MOTOR_STEER_FULL_LEFT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01)); ///< 1 bit(s) starting from B0

    raw = ((uint32_t)(((from->MOTOR_STEER_SLIGHT_LEFT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 1); ///< 1 bit(s) starting from B1

    raw = ((uint32_t)(((from->MOTOR_STEER_FULL_RIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 2); ///< 1 bit(s) starting from B2

    raw = ((uint32_t)(((from->MOTOR_STEER_SLIGHT_RIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 3); ///< 1 bit(s) starting from B3

    raw = ((uint32_t)(((from->MOTOR_STEER_STRAIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 4); ///< 1 bit(s) starting from B4

    raw = ((uint32_t)(((from->MOTOR_DRIVE_FORWARD)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 5); ///< 1 bit(s) starting from B5

    raw = ((uint32_t)(((from->MOTOR_DRIVE_REVERSE)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 6); ///< 1 bit(s) starting from B6

    raw = ((uint32_t)(((from->MOTOR_DRIVE_NEUTRAL)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 7); ///< 1 bit(s) starting from B7

    // Not doing min value check since the signal is unsigned already
    if(from->MOTOR_DRIVE_SPEED > 60) { from->MOTOR_DRIVE_SPEED = 60; } // Max value: 60
    raw = ((uint32_t)(((from->MOTOR_DRIVE_SPEED)))) & 0x3f;
    bytes[1] |= (((uint8_t)(raw) & 0x3f)); ///< 6 bit(s) starting from B8

    if(from->MOTOR_STEER_ANGLE < 10) { from->MOTOR_STEER_ANGLE = 10; } // Min value: 10
    if(from->MOTOR_STEER_ANGLE > 20) { from->MOTOR_STEER_ANGLE = 20; } // Max value: 20
    raw = ((uint32_t)(((from->MOTOR_STEER_ANGLE)))) & 0x7f;
    bytes[1] |= (((uint8_t)(raw) & 0x03) << 6); ///< 2 bit(s) starting from B14
    bytes[2] |= (((uint8_t)(raw >> 2) & 0x1f)); ///< 5 bit(s) starting from B16

    // Not doing min value check since the signal is unsigned already
    if(from->MOTOR_DRIVE_STOP > 1) { from->MOTOR_DRIVE_STOP = 1; } // Max value: 1
    raw = ((uint32_t)(((from->MOTOR_DRIVE_STOP)))) & 0x01;
    bytes[2] |= (((uint8_t)(raw) & 0x01) << 5); ///< 1 bit(s) starting from B21

    return MOTOR_SIGNAL_HDR;
}

/// Encode and send for dbc_encode_MOTOR_SIGNAL() message
static inline bool dbc_encode_and_send_MOTOR_SIGNAL(MOTOR_SIGNAL_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_MOTOR_SIGNAL(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_SENSOR_SONARS() since the sender is SENSOR and we are DRIVER

/// Not generating code for dbc_encode_CURRENT() since the sender is GPS and we are DRIVER

/// Decode BRIDGE's 'INITIAL_END' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_INITIAL_END(INITIAL_END_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != INITIAL_END_HDR.dlc || hdr->mid != INITIAL_END_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x01)); ///< 1 bit(s) from B0
    to->FLAG = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Decode BRIDGE's 'GPS_DESTINATION' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GPS_DESTINATION(GPS_DESTINATION_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != GPS_DESTINATION_HDR.dlc || hdr->mid != GPS_DESTINATION_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]))) << 8; ///< 8 bit(s) from B8
    raw |= ((uint32_t)((bytes[2]))) << 16; ///< 8 bit(s) from B16
    raw |= ((uint32_t)((bytes[3]))) << 24; ///< 8 bit(s) from B24
    to->GPS_DESTINATION_latitude = ((raw * 0.0001));
    raw  = ((uint32_t)((bytes[4]))); ///< 8 bit(s) from B32
    raw |= ((uint32_t)((bytes[5]))) << 8; ///< 8 bit(s) from B40
    raw |= ((uint32_t)((bytes[6]))) << 16; ///< 8 bit(s) from B48
    raw |= ((uint32_t)((bytes[7]))) << 24; ///< 8 bit(s) from B56
    to->GPS_DESTINATION_longitude = ((raw * 0.0001));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_MOTOR_SIGNAL() since 'DRIVER' is not the recipient of any of the signals

/// Decode SENSOR's 'SENSOR_SONARS' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SENSOR_SONARS(SENSOR_SONARS_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != SENSOR_SONARS_HDR.dlc || hdr->mid != SENSOR_SONARS_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]))) << 8; ///< 8 bit(s) from B8
    to->SENSOR_SONARS_left = ((raw));
    raw  = ((uint32_t)((bytes[2]))); ///< 8 bit(s) from B16
    raw |= ((uint32_t)((bytes[3]))) << 8; ///< 8 bit(s) from B24
    to->SENSOR_SONARS_middle = ((raw));
    raw  = ((uint32_t)((bytes[4]))); ///< 8 bit(s) from B32
    raw |= ((uint32_t)((bytes[5]))) << 8; ///< 8 bit(s) from B40
    to->SENSOR_SONARS_right = ((raw));
    raw  = ((uint32_t)((bytes[6]))); ///< 8 bit(s) from B48
    raw |= ((uint32_t)((bytes[7]))) << 8; ///< 8 bit(s) from B56
    to->SENSOR_SONARS_rear = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_CURRENT() since 'DRIVER' is not the recipient of any of the signals

/// Handle the MIA for BRIDGE's INITIAL_END message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_INITIAL_END(INITIAL_END_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= INITIAL_END__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = INITIAL_END__MIA_MSG;
        msg->mia_info.mia_counter_ms = INITIAL_END__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for BRIDGE's GPS_DESTINATION message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GPS_DESTINATION(GPS_DESTINATION_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GPS_DESTINATION__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = GPS_DESTINATION__MIA_MSG;
        msg->mia_info.mia_counter_ms = GPS_DESTINATION__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for SENSOR's SENSOR_SONARS message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SENSOR_SONARS(SENSOR_SONARS_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SENSOR_SONARS__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = SENSOR_SONARS__MIA_MSG;
        msg->mia_info.mia_counter_ms = SENSOR_SONARS__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

#endif
