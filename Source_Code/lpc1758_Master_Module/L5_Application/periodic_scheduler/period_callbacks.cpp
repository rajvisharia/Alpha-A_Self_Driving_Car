#include <_can_dbc/generated_can.h>
#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "can.h"
#include "switches.hpp"
#include "string.h"
#include "printf_lib.h"
#include "obstacle_avoidance.h"
#include "Indicators.h"

Switches& SW_obj = Switches::getInstance();
Indicator lights;

/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);

const uint32_t            SENSOR_SONARS__MIA_MS = 2000;
const SENSOR_SONARS_t     SENSOR_SONARS__MIA_MSG = {999};
const uint32_t            HEARTBEAT_BRIDGE__MIA_MS = 200;
const HEARTBEAT_BRIDGE_t  HEARTBEAT_BRIDGE__MIA_MSG = {0};
const uint32_t            HEARTBEAT_GPS__MIA_MS = 200;
const HEARTBEAT_GPS_t  	  HEARTBEAT_GPS__MIA_MSG = {0};

const uint32_t            		GPS_CAR_RUNNING__MIA_MS = 200;
const GPS_CAR_RUNNING_t  	 	GPS_CAR_RUNNING__MIA_MSG = {0};



/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
	//initializing the CAN bus
	CAN_init(can1, 100, 5, 5, nullptr, nullptr);
	//if receiving enable this code
	CAN_bypass_filter_accept_all_msgs();
	//resetting
	CAN_reset_bus(can1);

	//To be removed after integration
	SW_obj.init();
	init_indicator_gpio();
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
	if(CAN_is_bus_off(can1))
		CAN_reset_bus(can1);
}

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{
	can_msg_t msg;
	msg.msg_id = mid;
	msg.frame_fields.data_len = dlc;
	msg.frame_fields.is_29bit = 0;
	msg.frame_fields.is_rtr = 0;

	memcpy(msg.data.bytes, bytes, dlc);

	return CAN_tx(can1, &msg , 2);

}
void period_10Hz(uint32_t count)
{
	switch(lights.state)
	{
		case going_forward: 		turn_on_head_lights(0);
									turn_on_tail_lights(1);break;

		case going_reverse:			turn_on_head_lights(1);
									blink_tail_lights();break;

		case stopped:				turn_on_head_lights(1);
									turn_on_tail_lights(0);break;

		case destination_reached:	blink_head_lights();
									blink_tail_lights();break;

		default: 					blink_head_lights();
									turn_on_tail_lights(1);break;
	}
}

void period_100Hz(uint32_t count)
{
	can_msg_t received_CAN1_msg= {0};
			dbc_msg_hdr_t can_msg_hdr;

	MOTOR_SIGNAL_t *motor_msg_to_send;
	static SENSOR_SONARS_t sensor_msg_decoded = {0};
	static GPS_CAR_RUNNING_t gps_car_running = {0};

	static APP_START_STOP_t ble_start_signal = {0};

	static HEARTBEAT_BRIDGE_t bridge_heartbeat = {0};
	static HEARTBEAT_GPS_t gps_heartbeat = {0};

	if (CAN_is_bus_off(can1))
		CAN_reset_bus(can1);
		//Receive Sensor Data
	while(CAN_rx(can1, &received_CAN1_msg, 0))
	{
		can_msg_hdr.dlc = received_CAN1_msg.frame_fields.data_len;
		can_msg_hdr.mid = received_CAN1_msg.msg_id;

		if(received_CAN1_msg.msg_id == APP_START_STOP_HDR.mid)
			dbc_decode_APP_START_STOP(&ble_start_signal, received_CAN1_msg.data.bytes,&can_msg_hdr);
		else if(received_CAN1_msg.msg_id == SENSOR_SONARS_HDR.mid)
			dbc_decode_SENSOR_SONARS(&sensor_msg_decoded, received_CAN1_msg.data.bytes,&can_msg_hdr);
		else if(received_CAN1_msg.msg_id == HEARTBEAT_BRIDGE_HDR.mid)
			dbc_decode_HEARTBEAT_BRIDGE(&bridge_heartbeat, received_CAN1_msg.data.bytes,&can_msg_hdr);
		else if(received_CAN1_msg.msg_id == HEARTBEAT_GPS_HDR.mid)
			dbc_decode_HEARTBEAT_GPS(&gps_heartbeat, received_CAN1_msg.data.bytes, &can_msg_hdr);
		else if(received_CAN1_msg.msg_id == GPS_CAR_RUNNING_HDR.mid)
			dbc_decode_GPS_CAR_RUNNING(&gps_car_running, received_CAN1_msg.data.bytes, &can_msg_hdr);
	}

	// MIA Handling
	if(received_CAN1_msg.msg_id != SENSOR_SONARS_HDR.mid)
		dbc_handle_mia_SENSOR_SONARS(&sensor_msg_decoded, 10);
	if(received_CAN1_msg.msg_id != HEARTBEAT_BRIDGE_HDR.mid)
		dbc_handle_mia_HEARTBEAT_BRIDGE(&bridge_heartbeat, 10);
	if(received_CAN1_msg.msg_id != HEARTBEAT_GPS_HDR.mid)
		dbc_handle_mia_HEARTBEAT_GPS(&gps_heartbeat, 10);
	if(received_CAN1_msg.msg_id != GPS_CAR_RUNNING_HDR.mid)
		dbc_handle_mia_GPS_CAR_RUNNING(&gps_car_running, 10);


	//LED1 - Sensor_MIA, LED2- GPS_MIA, LED3-BLuetooth MIA
	LE.set(1, (bool)sensor_msg_decoded.mia_info.is_mia);
	LE.set(2, (bool)gps_heartbeat.mia_info.is_mia);
	LE.set(3, bridge_heartbeat.mia_info.is_mia);

	range_type left = get_left_state(sensor_msg_decoded.SENSOR_SONARS_left);
	range_type middle = get_center_state(sensor_msg_decoded.SENSOR_SONARS_middle);
	range_type right = get_right_state(sensor_msg_decoded.SENSOR_SONARS_right);
	range_type rear = get_rear_state(sensor_msg_decoded.SENSOR_SONARS_rear);


	motor_msg_to_send = (MOTOR_SIGNAL_t *) set_motor_direction_and_speed(&lights, left,middle,right,rear,gps_car_running);

	// If any of the GPS, Sensor module is disconnected or blue tooth App stop command occurs

	if(!ble_start_signal.BRIDGE_START)
		 motor_msg_to_send->MOTOR_DRIVE_SPEED = 0;

	// Send Motor Signal
	dbc_encode_and_send_MOTOR_SIGNAL(motor_msg_to_send);
}

void period_1000Hz(uint32_t count)
{
  //  LE.toggle(4);
}
