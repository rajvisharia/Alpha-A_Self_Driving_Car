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
#include "printf_lib.h"
#include "io.hpp"
#include "periodic_callback.h"
#include "lpc_pwm.hpp"
#include "stdio.h"
#include "gpio.hpp"
#include "utilities.h"
#include "can.h"
#include "motors_module.cpp"
#include "_can_dbc/generated_can.h"
#include "eint.h"



//const uint32_t				MOTOR_SIGNAL__MIA_MS = 3000;
//const MOTOR_SIGNAL_t 		MOTOR_SIGNAL__MIA_MSG = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};


/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);


/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);


const uint32_t MOTOR_SIGNAL__MIA_MS = 500;
const MOTOR_SIGNAL_t MOTOR_SIGNAL__MIA_MSG = {0};
MOTOR_SIGNAL_t motor_signal;
can_t can_1 = can1;

// Function Declarations for Servo motor and DC motor.
bool servo_motor_steer_angle (MOTOR_SIGNAL_t motor_signal);
bool dc_motor_drive_speed (MOTOR_SIGNAL_t motor_signal);



/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
	if(CAN_init(can_1, 100, 80, 80, NULL, NULL))
	{
		//u0_dbg_printf("CAN init successful\n");
		CAN_reset_bus(can_1);
		CAN_bypass_filter_accept_all_msgs();
	}

	motor_signal.mia_info.is_mia = false;
	motor_signal.mia_info.mia_counter_ms = 0;

	Rfptr = &read_rising_RPM_fe;
	eint3_enable_port2(4, eint_rising_edge, Rfptr);

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
	// Reset in case of bus off state.
	if(CAN_is_bus_off(can_1))
	{
		CAN_reset_bus(can_1);
	}
}


void period_10Hz(uint32_t count)
{

}


void period_100Hz(uint32_t count)
{
	can_msg_t can_msg;

	while (CAN_rx(can_1, &can_msg, 0))
	{
		dbc_msg_hdr_t msg_hdr;
		msg_hdr.mid = can_msg.msg_id;
		msg_hdr.dlc = can_msg.frame_fields.data_len;
		dbc_decode_MOTOR_SIGNAL(&motor_signal, can_msg.data.bytes, &msg_hdr);
	}

	if (dbc_handle_mia_MOTOR_SIGNAL(&motor_signal, 10))			// Changed from if to while...Check once.
	{
		motor_signal.MOTOR_DRIVE_REVERSE = 0;
		//motor_signal.MOTOR_STEER_STRAIGHT = 0;
		motor_signal.MOTOR_STEER_STRAIGHT = 1;
	}

	// Function calls for servo and dc motor.
	servo_motor_steer_angle (motor_signal);
	dc_motor_drive_speed (motor_signal);

}


// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    //LE.on(4);
}


