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
#include "io.hpp"
#include "periodic_callback.h"
#include "_can_dbc/generated_can.h"
#include "can.h"
#include "uart3.hpp"
#include "switches.hpp"
#include "string.h"
#include "printf_lib.h"
#include "source/gps_module.h"
#include "source/i2cMagmtr.h"




/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);

//const uint32_t GPS_CHECKPOINT_DESTINATION__MIA_MS = 30000;
//const GPS_CHECKPOINT_DESTINATION_t GPS_CHECKPOINT_DESTINATION__MIA_MSG = {373362 , 1218819, 1, 0}; //mia message

GPS_CHECKPOINT_DESTINATION_t gps_des;
GPS_CURRENT_LOCATION_t gps_curr;
HEARTBEAT_GPS_t gps_hb;
GPS_CAR_RUNNING_t gps_dir;
GPS_BEARING_HEADING_t gps_angle;


can_t can_1 = can1;

Uart3& u3 = u3.getInstance();

i2cMagmtr ic;

uint16_t b_can;
uint16_t h_can;

char *c = new char[1];


float lat1, long1, long2, lat2;
int lat_f = 0, long_f = 0;
float lat_curr = 0, long_curr = 0;

int k = 0;   //used for compass heading angle printing on console

bool GPS_ON = false;
bool COMPASS_ON = false;
bool DEST_MSG_RECEIVED = false;






/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{

    if(CAN_init(can_1, 100, 500, 500, NULL, NULL))
    {
        u0_dbg_printf("init up\n");
    }

    CAN_reset_bus(can_1);
    CAN_bypass_filter_accept_all_msgs();

//    gps_des.GPS_latitude = 000000;
//    gps_des.GPS_longitude = 000000;
//    gps_des.mia_info.is_mia = false;
//    gps_des.mia_info.mia_counter_ms = 0;

	u3.init(9600, 100, 0);

	if (I2C2::getInstance().checkDeviceResponse(0xC0))
	{
		//			u0_dbg_printf("Discovered sensor CMPS11");
	}

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

void period_1Hz(uint32_t count)
{
	if(SW.getSwitch(4))
	{
		if(SW.getSwitch(3))
		{
			u0_dbg_printf("calib/n");
			ic.calibrate();
		}
	}

	if(SW.getSwitch(1))
	{
		u0_dbg_printf("stop/n");
		ic.calibrate_stop();
	}

    if(CAN_is_bus_off(can_1))
    {
    	CAN_reset_bus(can_1);
    }


        can_msg_t can_msg_tx;
        dbc_msg_hdr_t tx_msg_hdr;

        gps_curr.GPS_CURRENT_LOCATION_latitude = lat_f;
        gps_curr.GPS_CURRENT_LOCATION_longitude = long_f;


        tx_msg_hdr = dbc_encode_GPS_CURRENT_LOCATION(can_msg_tx.data.bytes, &gps_curr);
        can_msg_tx.frame_fields.data_len = tx_msg_hdr.dlc;
        can_msg_tx.msg_id = tx_msg_hdr.mid;
        can_msg_tx.frame_fields.is_rtr = 0;
        can_msg_tx.frame_fields.is_29bit = 0;

        //need some change after discussion with kathan!!!!
        //if((lat1 < 38 && lat1 > 36) && (long1 > -123 && long1 < -120))

        if(GPS_ON)
        {
            if(CAN_tx(can1, &can_msg_tx, 0))
            {

            }
        }

        can_msg_t angle_msg;
        dbc_msg_hdr_t angle_msg_hdr;

        gps_angle.GPS_BEARING_angle = b_can;
        gps_angle.GPS_HEADING_angle = h_can;
        gps_angle.GPS_COMPASS_ON = COMPASS_ON;
        gps_angle.GPS_GPS_ON = GPS_ON;
        gps_angle.GPS_DEST_RECEIVED = DEST_MSG_RECEIVED;

        if(!GPS_ON)
        {
        	gps_angle.GPS_BEARING_angle = -1;
        }
        else
        {
        	LE.toggle(1); //GPS LOCK
        }

        if(!COMPASS_ON)
        {
        	gps_angle.GPS_HEADING_angle = -1;
        }

        angle_msg_hdr = dbc_encode_GPS_BEARING_HEADING(angle_msg.data.bytes, &gps_angle);
        angle_msg.frame_fields.data_len = angle_msg_hdr.dlc;
        angle_msg.msg_id = angle_msg_hdr.mid;
        angle_msg.frame_fields.is_rtr = 0;
        angle_msg.frame_fields.is_29bit = 0;

        if(CAN_tx(can1, &angle_msg, 0))
        {

        }
}




void period_10Hz(uint32_t count)
{
	can_msg_t hb_msg;
	dbc_msg_hdr_t hb_msg_hdr;

	gps_hb.GPS_CONNECTED = 1;

	hb_msg_hdr = dbc_encode_HEARTBEAT_GPS(hb_msg.data.bytes, &gps_hb);
	hb_msg.frame_fields.data_len = hb_msg_hdr.dlc;
	hb_msg.msg_id = hb_msg_hdr.mid;
	hb_msg.frame_fields.is_rtr = 0;
	hb_msg.frame_fields.is_29bit = 0;

	if(CAN_tx(can1, &hb_msg, 0))
	{

    }

	uint8_t rx = 0;

    can_msg_t gps_dest_msg;

    while(CAN_rx(can_1, &gps_dest_msg, 0))
    {
        dbc_msg_hdr_t des_hdr;
        des_hdr.dlc = gps_dest_msg.frame_fields.data_len;
        des_hdr.mid = gps_dest_msg.msg_id;

        if(gps_dest_msg.msg_id == GPS_CHECKPOINT_DESTINATION_HDR.mid)
        {
        	dbc_decode_GPS_CHECKPOINT_DESTINATION(&gps_des, gps_dest_msg.data.bytes, &des_hdr);

            lat2 = static_cast<float>(gps_des.GPS_latitude)/1000000;
            long2 = static_cast<float>(gps_des.GPS_longitude)/1000000;
            long2 *= -1;

            DEST_MSG_RECEIVED = true;
            rx = 1;
        }

        //move the car only on receiving the destination checkpoint

    }

    if(rx == 0)
    {
    	LE.toggle(2);   //DESTINATION NOT RECEIVING BLINK;
    	DEST_MSG_RECEIVED = false;
    	//if destination not receiving from the bridge, blink something on the SJ ONE board
    }
}



void period_100Hz(uint32_t count)
{

	uint16_t hAngle;
	uint16_t Z;

	if(ic.getData(Z))
	{
		hAngle = (Z)/10;
		COMPASS_ON = true;
	}
	else
	{
		// compass not returning any value
		hAngle = -1;
		COMPASS_ON = false;
	}

	h_can = hAngle;

	if(SW.getSwitch(2))
	{
		//k should be global
		k = 1;
	}
	else if(SW.getSwitch(3))
	{
		k = 0;
	}

	if(k == 1)
	{
		u0_dbg_printf(" Heading angle %d \n", h_can);
	}


	uint8_t sat_count[2];
	int lat_e = 0, long_e = 0;
	float lat_ef = 0.00, long_ef = 0.00;
	int lat_G = 0;
	int long_G = 0;


    u3.getChar(c, 0);
    int g;
    int div = 1;

    if(*c == '$')
    {
        u3.getChar(c, 0);
        if(*c == 'G')
        {
            u3.getChar(c, 0);
            if(*c == 'P')
            {
                u3.getChar(c, 0);
                if(*c == 'G')
                {
                    u3.getChar(c, 0);
                    if(*c == 'G')
                    {
                        u3.getChar(c, 0);
                        if(*c == 'A')
                        {
                            u3.getChar(c, 0);
                            if(*c == ',')
                            {
                                u3.getChar(c, 0);
                                while(*c != ',')
                                {
                                    u3.getChar(c, 0);
                                }
                                if(*c == ',')
                                {
                                    lat_G = 0;
                                    lat_e = 0;
                                    lat_ef = 0;
                                    lat1 = 0;


                                    u3.getChar(c, 0);

                                    g = *c-'0';
                                    lat_G += g*10000000/div;
                                    div *= 10;

                                    u3.getChar(c, 0);
                                    g = *c-'0';
                                    lat_G += g*10000000/div;
                                    div *= 10;

                                    u3.getChar(c, 0);
                                    while(*c != ',')
                                    {
                                        if(*c != '.')
                                        {
                                            g = *c-'0';
                                            lat_e += g*10000000/div;
                                            div *= 10;
                                        }

                                        u3.getChar(c, 0);
                                    }

                                    lat_ef = static_cast<float>(lat_e)/60;
                                    lat1 = static_cast<float>(lat_G)/100 + lat_ef;
                                    lat_ef *= 100;
                                    lat_f = lat_G + static_cast<int>(lat_ef);


                                    if(*c == ',')
                                    {
                                        u3.getChar(c,0);
                                        u3.getChar(c,0);
                                        u3.getChar(c,0);
                                        div = 1;

                                        long_G = 0;
                                        long_e = 0;
                                        long_ef = 0;
                                        long1 = 0;


                                        g = *c-'0';
                                        long_G += g*100000000/div;
                                        div *= 10;

                                        u3.getChar(c, 0);
                                        g = *c-'0';
                                        long_G += g*100000000/div;
                                        div *= 10;

                                        u3.getChar(c, 0);
                                        g = *c-'0';
                                        long_G += g*100000000/div;
                                        div *= 10;

                                        u3.getChar(c,0);

                                        while(*c != ',')
                                        {
                                            if(*c != '.')
                                            {
                                                g = *c-'0';
                                                long_e += g*100000000/div;
                                                div *= 10;
                                            }

                                            u3.getChar(c,0);
                                        }

                                        long_ef = static_cast<float>(long_e)/60;
                                        long1 = static_cast<float>(long_G)/100 + long_ef;
                                        long_ef *= 100;
                                        long_f = long_G + static_cast<int>(long_ef);



                                        lat1 = (lat1)/10000;
                                        long1 = -1*(long1)/10000;

                                        u3.getChar(c,0);  // W,
                                        u3.getChar(c,0);  // ,
                                        u3.getChar(c,0);  // 1
                                        u3.getChar(c,0);  // ,
                                        u3.getChar(c,0);  // satellite first digit
                                        LD.setLeftDigit(*c);

                                        if(*c > 0)
                                        {
                                             LE.toggle(1);
                                        }
                                        sat_count[0] = *c;

                                        u3.getChar(c,0);  //satellite second digit
                                        LD.setRightDigit(*c);

                                        if(*c > 0)
                                        {
                                             LE.toggle(1);
                                        }
                                        sat_count[1] = *c;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if((lat1 < 38 && lat1 > 36) && (long1 > -123 && long1 < -120))
    {
 	   lat_curr = lat1;
 	   long_curr = long1;
 	   GPS_ON = true;
 	   //can use one more bool variable GPS_SET and move the GPS_ON to the satellite checking 'if loop'
    }
    else
    {
 	   GPS_ON = false;
 	   //GPS values are incorrect
    }


    //dir_msg would be 7 initially so, that car will not move
    uint8_t dir_msg = 7;

    //initially the distance is -1, once we compute it changes
    int dist = -1;

    float bAngle = -1;

    /*
     * we make the calculation to move the car only if the GPS_SET, COMPASS_ON and
     * if DESTINATION message is received from the bridge
     *  else, set dir_msg to 7, which tells the master to stop the motors so that car
     *  doesn't move
     */

    if(GPS_ON && COMPASS_ON && DEST_MSG_RECEIVED)
    {
    	bAngle = bearing_angle(lat_curr, long_curr, lat2, long2);

        if(bAngle < 0)
        {
     	   bAngle += 360;
        }

        float degree = static_cast<float>(hAngle) - bAngle;

        dist = distance(lat_curr, long_curr, lat2, long2);

     	dir_msg = turn_direction(degree);


     	if(dist < 10)
     	{
     		LE.toggle(3);
     		dir_msg = 7;  //stop the car
     	}
    }
    else
    {
    	LE.toggle(4);
    	dir_msg = 8; //stop the car if we don't receive any of the data
    }

    b_can = static_cast<int>(bAngle);

 	can_msg_t motor_turn_msg;
 	dbc_msg_hdr_t motor_turn_msg_hdr;

 	gps_dir.GPS_CAR_ANGLE_TURN_dirmsg = dir_msg;
 	gps_dir.GPS_CAR_DISTANCE_to_destination = dist;
 	gps_dir.GPS_SAT_COUNT_TENS_DIGIT = sat_count[0];
 	gps_dir.GPS_SAT_COUNT_UNIT_DIGIT = sat_count[1];

 	motor_turn_msg_hdr = dbc_encode_GPS_CAR_RUNNING(motor_turn_msg.data.bytes, &gps_dir);
 	motor_turn_msg.frame_fields.data_len = motor_turn_msg_hdr.dlc;
 	motor_turn_msg.msg_id = motor_turn_msg_hdr.mid;
 	motor_turn_msg.frame_fields.is_rtr = 0;
 	motor_turn_msg.frame_fields.is_29bit = 0;

<<<<<<< HEAD
	if(CAN_tx(can1, &motor_turn_msg, 0))
	{

         LE.toggle(4);

    }
||||||| merged common ancestors
	if(CAN_tx(can1, &motor_turn_msg, 0))
	{
         LE.toggle(4);
    }
=======
 	if(CAN_tx(can1, &motor_turn_msg, 0))
 	{
 		 LE.toggle(3);
 	}
>>>>>>> GPSModule

}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{

}
