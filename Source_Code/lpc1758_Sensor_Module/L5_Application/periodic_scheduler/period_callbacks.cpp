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


*
 * @file
 * This contains the period callback functions for the periodic scheduler
 *
 * @warning
 * These callbacks should be used for hard real-time system, and the priority of these
 * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
 * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
 * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
 * do must be completed within 1ms.  Running over the time slot will reset the system.*/


#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "lpc_pwm.hpp"
#include "LPC17xx.h"
#include "gpio.hpp"
#include "printf_lib.h"
#include "lpc_timers.h"
#include "core_cm3.h"
#include "semphr.h"
#include "lpc_sys.h"
#include "lpc_isr.h"
#include "eint.h"
#include "utilities.h"
#include "printf_lib.h"
#include "sensor.hpp"
#include "can.h"
#include "_can_dbc/generated_can.h"
#include <string.h>


/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
uint8_t DIST = 60;

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum*/

const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
//CAN communication
//can_t myCan = can1;
//POWER UP RIGHT and LEFT SENSOR -VCC
GPIO vccRt(P0_0);
GPIO vccLt(P0_1);
//GPIO vccBk(P0_29);

//init sensors
sensor senMid(middle);
sensor senLt(left);
sensor senRt(right);
sensor senBk(back);

//next sensor to be triggered
sensr next;

void (*Mfptr) (void);
void (*Rfptr) (void);
void (*Lfptr) (void);
void (*Bfptr) (void);

can_msg_t senMsg;
can_msg_t prevMsg;

extern "C"
{
void read_midSensr_fe(void)
{
    senMid.calculateDistance(middle);
}
void read_leftSensr_fe(void)
{
    senLt.calculateDistance(left);
}
void read_rightSensr_fe(void)
{
    senRt.calculateDistance(right);
}
void read_backSensr_fe(void)
{
    senBk.calculateDistance(back);
}
}

/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
// first sensor to be triggered is next
    next = middle;

    //power up right
    vccRt.setAsOutput();
    vccRt.setHigh();

    //power up left
    vccLt.setAsOutput();
    vccLt.setHigh();

    //power up back
   // vccBk.setAsOutput();
  //  vccBk.setHigh();

    //power up delays
    senMid.powerUpDelay();
    senRt.powerUpDelay();
    senLt.powerUpDelay();
    senBk.powerUpDelay();

    //interrupt callbacks
    Mfptr =&read_midSensr_fe;
    Rfptr =&read_rightSensr_fe;
    Lfptr =&read_leftSensr_fe;
    Bfptr = &read_backSensr_fe;
    //enable falling edge interrupts
    senMid.enableFEdge(Mfptr);
    senLt.enableFEdge(Lfptr);
    senRt.enableFEdge(Rfptr);
    senBk.enableFEdge(Bfptr);
    //LEDS to indicate obstacles
    LE.set(1,0);
    LE.set(2,0);
    LE.set(3,0);
    LE.set(4,0);

    //init Can
//    CAN_init(myCan,100,10,10,NULL,NULL);
//    //reset the can bus
//    CAN_reset_bus(myCan);
    return true; // Must return true upon success
}

/// Register any telemetry variables
bool period_reg_tlm(void)
{
    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
    return true; // Must return true upon success
}

void period_1Hz(uint32_t count)
{
//    if(CAN_is_bus_off(myCan))
//          CAN_reset_bus(myCan);
}

void period_10Hz(uint32_t count) //100ms
{

}

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{
//    can_msg_t can_msg = { 0 };
//    can_msg.msg_id= mid;
//    can_msg.frame_fields.data_len = dlc;
//    memcpy(can_msg.data.bytes, bytes, dlc);
//    bool sent = CAN_tx(myCan, &can_msg, 0);
//    //u0_dbg_printf("%d",sent);
//    return sent;
}

void period_100Hz(uint32_t count)  //10ms
{
//	if(count%6 == 0)
//	senBk.commandRanging();
//	bool distinct = false;
    if(count%6 == 0)
    {
        if(next == middle)
        {
            senMid.commandRanging();
            if(senMid.distance < DIST)
            	LE.set(1,1);
            else
            	LE.set(1,0);
            next = right;
        }
        else if(next == right)
        {
            senRt.commandRanging();
			if (senRt.distance < DIST)
				LE.set(2,1);
			else
				LE.set(2,0);
            next = left;
        }
        else if(next == left)
        {
            senLt.commandRanging();
			if (senLt.distance < DIST)
				LE.set(3,1);
			else
				LE.set(3,0);
            next = back;
       }
        else if(next == back)
        {
             senBk.commandRanging();
        	 if(senBk.distance < DIST)
        	     LE.set(4,1);
        	 else
        	     LE.set(4,0);
        	 next = middle;
//        	            sending the CAN message
//        				for (int i = 0; i < 8; i++) {
//        					prevMsg.data.bytes[i]=senMsg.data.bytes[i];
//        				}
//        	            SENSOR_SONARS_t sen_msg = { 0 };

//        	            sen_msg.SENSOR_SONARS_middle = (uint16_t)senMid.distance;
//        	            sen_msg.SENSOR_SONARS_left =   (uint16_t)senLt.distance;
//        	            sen_msg.SENSOR_SONARS_right =  (uint16_t)senRt.distance;
//        	            sen_msg.SENSOR_SONARS_rear =   (uint16_t)senRt.distance;
        	            // This function will encode the CAN data bytes, and send the CAN msg using dbc_app_send_can_msg()
//        	            dbc_encode_and_send_SENSOR_SONARS(&sen_msg);
//        	            code to send distinct messages
//        	            dbc_encode_SENSOR_SONARS(senMsg.data.bytes,&sen_msg);
//        	            for(int i=0;i<8;i++)
//        	            {
//        	            	if( prevMsg.data.bytes[i]!=senMsg.data.bytes[i])
//        	            	{
//        	            		distinct = true;
//        	            		break;
//        	            	}
//        	            }
//        	            if(distinct)
//        	            	CAN_tx(myCan,&senMsg,10);



        }
    }

}

void period_1000Hz(uint32_t count)
{

}
