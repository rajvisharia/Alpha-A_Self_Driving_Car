/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * This contains the period callback functions for the periodic scheduler
 *
 * @warning
 * These callbacks should be used for hard real-time system, and the priority of these
 * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
 * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
 * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
 * do must be completed within 1ms.  Running over the time slot will reset the system.
 */

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "gpio.hpp"
#include "eint.h"
#include "can.h"
#include "printf_lib.h"
#include "_can_dbc/generated_can.h"
#include "uart2.hpp"
#include "blue.h"
#include "printf_lib.h"
#include "utilities.h"


bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{
    can_msg_t can_msg             = { 0 };
    can_msg.msg_id                = mid;
    can_msg.frame_fields.data_len = dlc;
    memcpy(can_msg.data.bytes, bytes, dlc);

    return CAN_tx(can1, &can_msg, 0);
}

Uart2& bluetooth = Uart2::getInstance();


/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);

/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    CAN_init(can1,100, 10, 10, NULL, NULL);
    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(can1);
    bluetooth.init(9600, 1250, 350);
    return true; // Must return true upon success
}

/// Register any telemetry variables
bool period_reg_tlm(void)
{
    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
    return true; // Must return true upon success
}


/**
 * Below are your periodic functions.
 * The argument 'count' is the number of times each periodic task is called.
 */



//static blue inst;
char *c = new char[1];
int lat_can = 0, long_can = 0;
int checkpoint_index_on_CAN = 0;
bool flag_START_received = false;
bool flag_STOP_received = false;
int prev_LAT_on_CAN = 0;
int prev_LNG_on_CAN = 0;
bool flag_RETRANSMISSION_on_CAN = false;

APP_START_STOP_t startstop;
GPS_CHECKPOINT_DESTINATION_t coordinates;
HEARTBEAT_BRIDGE_t bridge_heartbeat;


/*  MIA handling*/
const uint32_t GPS_CURRENT_LOCATION__MIA_MS = 1000;
const uint32_t GPS_BEARING_HEADING__MIA_MS = 1500;
const uint32_t GPS_CAR_RUNNING__MIA_MS = 2000;
//const uint32_t SPEED_RPM__MIA_MS = 4000;

GPS_CURRENT_LOCATION_t GPS_location = {0};
const GPS_CURRENT_LOCATION_t  GPS_CURRENT_LOCATION__MIA_MSG = {0};
GPS_BEARING_HEADING_t Bearing_Heading = {0};
const GPS_BEARING_HEADING_t GPS_BEARING_HEADING__MIA_MSG = {0};
GPS_CAR_RUNNING_t Distance_Angle = {0};
const GPS_CAR_RUNNING_t GPS_CAR_RUNNING__MIA_MSG = {0};
//SPEED_RPM_t Speed = {0};
//const SPEED_RPM_t SPEED_RPM__MIA_MSG = {0};
int flag_100Hz = 0;

void period_1Hz(uint32_t count)
{
    if (CAN_is_bus_off(can1))   CAN_reset_bus(can1);
    if(count % 2 == 0) bridge_heartbeat.BRIDGE_CONNECTED = 1;
    else bridge_heartbeat.BRIDGE_CONNECTED = 0;
    dbc_encode_and_send_HEARTBEAT_BRIDGE(&bridge_heartbeat);
}

int temp_COUNT = 0;

void period_10Hz(uint32_t count)
{
/*
	char finalMsg[24] ="";
    int flag = 0;
    bool recd = false;
    double lati_tude  = 0.0;
    double longi_tude = 0.0;
    int index=0;

    while(bluetooth.getRxQueueSize() > 0)
    {
        bluetooth.getChar(c,5);
        //bluetooth.gets(finalMsg,23,3);
        //u0_dbg_printf("%s \n", finalMsg);
        //u0_dbg_printf("%c", *c);
        if(*c != '\n'){
        	//u0_dbg_printf("%c", *c);
            finalMsg[index] = c[0];
            recd = true;
            index++;

        }
        else
        {
            finalMsg[index] = c[0];//handle the newline
           // u0_dbg_printf("nl");
            break;
        }

    }

    if(recd)
    {
        //u0_dbg_printf("fin msg %s", finalMsg);
        flag = validate_store(finalMsg);

        if (flag > 0) {
           // startstop.BRIDGE_START = (uint8_t) get_startstop();
           // u0_dbg_printf("start stop %d",get_startstop());
        	//handling lat long
        	//handling start stop
			if (flag == 1) {
				if (get_startstop() == 1) {
					startstop.BRIDGE_START = 1;
					flag_START_received = true;
				}
				if (get_startstop() == 0) {

					startstop.BRIDGE_START = 0;
					checkpoint_index_on_CAN = 0;
					flag_STOP_received = true;
				}
//				u0_dbg_printf("startstopbrig %d  \n", startstop.BRIDGE_START);
				if (flag_START_received || flag_STOP_received) {
					dbc_encode_and_send_APP_START_STOP(&startstop);
					flag_START_received = false;
					flag_STOP_received = false;

				}
			}
			if (flag == 2) {
//				lati_tude = get_latitude(checkpoint_index_on_CAN);
//				lat_can = (int) (lati_tude * (1000000));
//				coordinates.GPS_latitude = lat_can;
//
//				longi_tude = get_longitude(checkpoint_index_on_CAN);
//				long_can = (int) (longi_tude * (1000000) *-1);
//				coordinates.GPS_longitude = long_can;
//
//				if(dbc_encode_and_send_GPS_CHECKPOINT_DESTINATION(&coordinates)){
//					u0_dbg_printf(
//							"LAT: %d & LON: %d   @idx: %d  \n",
//							coordinates.GPS_latitude, coordinates.GPS_longitude,
//							checkpoint_index_on_CAN);
//					checkpoint_index_on_CAN++;
//				}
			}
        }
    }

    //deciding which coord to send and sending it
    //if current coord < last coord increment else repeat last coord
    if(Distance_Angle.GPS_CAR_ANGLE_TURN_dirmsg == 7){
		if(checkpoint_index_on_CAN < (get_checkpoints()-1)) checkpoint_index_on_CAN++;
		else checkpoint_index_on_CAN = get_checkpoints()-1;
    }
    //send the checkpoint------------------------------->
	lat_can = (int)(get_latitude(checkpoint_index_on_CAN) * 1000000);
	coordinates.GPS_latitude = lat_can;
	long_can = (int)(get_longitude(checkpoint_index_on_CAN) * 1000000 *-1);
	coordinates.GPS_longitude  = long_can;
	if(coordinates.GPS_latitude != 0 || coordinates.GPS_longitude != 0){
		u0_dbg_printf("LATITUDE: %d & LONGITUDE: %d", coordinates.GPS_latitude, coordinates.GPS_longitude);
		dbc_encode_and_send_GPS_CHECKPOINT_DESTINATION(&coordinates);
		flag_RETRANSMISSION_on_CAN = false;
	}
	else{
		flag_RETRANSMISSION_on_CAN = true;
	}

	if(coordinates.GPS_latitude != 0) prev_LAT_on_CAN = lat_can;
	if(coordinates.GPS_longitude != 0) prev_LNG_on_CAN = long_can;

	if(flag_RETRANSMISSION_on_CAN){
		coordinates.GPS_latitude = prev_LAT_on_CAN;
		coordinates.GPS_longitude = prev_LNG_on_CAN;
		u0_dbg_printf("LATITUDE: %d & LONGITUDE: %d", coordinates.GPS_latitude, coordinates.GPS_longitude);
		dbc_encode_and_send_GPS_CHECKPOINT_DESTINATION(&coordinates);
		flag_RETRANSMISSION_on_CAN = false;
	}
*/
//---------------------------------

	double latitude[7] = {37.335987, 37.335772, 37.335512, 37.335391, 37.335163, 37.334945, 37.334973};
	double longitude[7] = {121.881847, 121.881704, 121.881505, 121.881392, 121.881255, 121.881096, 121.880920};

	if(Distance_Angle.GPS_CAR_ANGLE_TURN_dirmsg == 7){
		if(temp_COUNT < 6) temp_COUNT++;
		else temp_COUNT = 6;
	}
	else{
	}
    coordinates.GPS_latitude = (int)(latitude[temp_COUNT] * 1000000);
	coordinates.GPS_longitude = (int)(longitude[temp_COUNT] * 1000000);
	if(coordinates.GPS_latitude != 0 || coordinates.GPS_longitude != 0){
		u0_dbg_printf("LATITUDE: %d & LONGITUDE: %d", coordinates.GPS_latitude, coordinates.GPS_longitude);
		dbc_encode_and_send_GPS_CHECKPOINT_DESTINATION(&coordinates);
	}

//---------------------------------/
    char to_Android_Lat_Long_Heading[35];
    char *ptr = to_Android_Lat_Long_Heading;
/*  int temp_index = 0;*/
    double temp_Lat = GPS_location.GPS_CURRENT_LOCATION_latitude * 0.000001;
    double temp_Long = GPS_location.GPS_CURRENT_LOCATION_longitude * (0.000001) * (-1);
    double temp_Heading = Bearing_Heading.GPS_HEADING_angle;

    sprintf(to_Android_Lat_Long_Heading, "#%f@%f*%f\n", temp_Lat, temp_Long, temp_Heading);

    while(*ptr != '\n'){
        bluetooth.putChar(*ptr);
        ptr++;
    }
    bluetooth.putChar( '\n' );
}



void period_100Hz(uint32_t count)
{
    can_msg_t can_msg;

    while(CAN_rx(can1, &can_msg, 0))
    {
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;

        if(can_msg_hdr.mid == 555) {
            dbc_decode_GPS_CURRENT_LOCATION( &GPS_location, can_msg.data.bytes, &can_msg_hdr);
//          u0_dbg_printf("%d ", GPS_location.GPS_CURRENT_LOCATION_latitude);
//          u0_dbg_printf("%d ", GPS_location.GPS_CURRENT_LOCATION_longitude);
            flag_100Hz = 1;
        }
        if(can_msg_hdr.mid == 540) {
            dbc_decode_GPS_BEARING_HEADING( &Bearing_Heading, can_msg.data.bytes, &can_msg_hdr);
//          u0_dbg_printf("%u ", Bearing_Heading.GPS_BEARING_angle);
            flag_100Hz = 2;
        }

        if(can_msg_hdr.mid == 400) {
            dbc_decode_GPS_CAR_RUNNING( &Distance_Angle, &can_msg.data.bytes[0], &can_msg_hdr);
            flag_100Hz = 3;
        }

/*
        if(can_msg_hdr.mid == 688) {
            dbc_decode_SPEED_RPM( &Speed, can_msg.data.bytes, &can_msg_hdr);
            flag_100Hz = 4;

        }
*/
    }

    if(dbc_handle_mia_GPS_CURRENT_LOCATION(&GPS_location, 10)) LE.toggle(1);
    if(dbc_handle_mia_GPS_BEARING_HEADING(&Bearing_Heading, 10)) LE.toggle(2);
    if(dbc_handle_mia_GPS_CAR_RUNNING(&Distance_Angle, 10)) LE.toggle(3);
//  if(dbc_handle_mia_SPEED_RPM(&Speed, 10)) LE.toggle(4);


}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
//    LE.toggle(4);
}
