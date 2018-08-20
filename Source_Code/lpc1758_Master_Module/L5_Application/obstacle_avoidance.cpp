/*
 * obstacle_avoidance.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: Jigar
 */

#include "generated_can.h"
#include "obstacle_avoidance.h"
#include "Indicators.h"
#include  "string.h"
#include "printf_lib.h"

range_type get_left_state(uint16_t left_rdg)
{
	dir_range range = {0};
	if(left_rdg>=0 && left_rdg <=40)
		range.left_range = too_near;
	else if(left_rdg>40 && left_rdg<=80)
		range.left_range = near;
	else if(left_rdg>80 && left_rdg<=180)
		range.left_range = far;
	else if(left_rdg > 180)
		range.left_range = too_far;

	return range.left_range;
}

range_type get_right_state(uint16_t right_rdg)
{
	dir_range range = {0};

	if(right_rdg>=0 && right_rdg <=40)
		range.right_range = too_near;
	else if(right_rdg>40 && right_rdg<=80)
		range.right_range = near;
	else if(right_rdg>80 && right_rdg<=180)
		range.right_range = far;
	else if(right_rdg > 180)
		range.right_range = too_far;

	return range.right_range;
}

range_type get_center_state(uint16_t center_rdg)
{
	dir_range range = {0};

	if(center_rdg>=0 && center_rdg <=40)
		range.center_range = too_near;
	else if(center_rdg>40 && center_rdg<=80)
		range.center_range = near;
	else if(center_rdg>80 && center_rdg<=180)
		range.center_range = far;
	else if(center_rdg > 180)
		range.center_range = too_far;

	return range.center_range;
}

range_type get_rear_state(uint16_t rear_rdg)
{
	dir_range range = {0};
	if(rear_rdg>=0 && rear_rdg <=40)
		range.rear_range = too_near;
	else if(rear_rdg>40 && rear_rdg<=80)
		range.rear_range = near;
	else if(rear_rdg>80 && rear_rdg<=180)
		range.rear_range = far;
	else if(rear_rdg > 180)
		range.rear_range = too_far;

	return range.rear_range;
}

ride_states get_rear_status(range_type rear)
{
	ride_states car_should= stop;
	if(rear == too_near)
		car_should = stop;
	else
		car_should = go_reverse;
	return car_should;
}

ride_states gps_drive_mode(GPS_CAR_RUNNING_t gps_car_running)
{
	ride_states car_should= stop;

	switch(gps_car_running.GPS_CAR_ANGLE_TURN_dirmsg)
	{
		case 0: car_should = turn_left;break;
		case 1: car_should = slight_left;break;
		case 2: car_should = very_slight_left;break;
		case 3: car_should = go_straight;break;
		case 4: car_should = very_slight_right;break;
		case 5: car_should = slight_right;break;
		case 6: car_should = turn_right;break;
		default: car_should = stop;
	}
	return car_should;
}

ride_states get_turn_status(range_type left, range_type right, range_type rear,GPS_CAR_RUNNING_t gps_car_running)
{
	ride_states car_should = stop;

	if((left == too_near) && (right == too_near)) car_should = get_rear_status(rear);
	else if((left == too_near) && right >= near) car_should = turn_right;
	else if(left >= near && (right == too_near)) car_should = turn_left;
	else	car_should = gps_drive_mode(gps_car_running);
	return car_should;
}

ride_states get_direction(range_type left, range_type center, range_type right, range_type rear,GPS_CAR_RUNNING_t gps_car_running)
{
	ride_states state = stop;
	switch(center)
	{
		case too_near: state = get_rear_status(rear);  break;
			case near:
			case far :
		case too_far : state = get_turn_status(left, right, rear, gps_car_running); break;
		default      : state = stop;
	}
	return state;
}

void* set_motor_direction_and_speed(Indicator *car, range_type left, range_type center, range_type right, range_type rear, GPS_CAR_RUNNING_t gps_car_running)
{
	static MOTOR_SIGNAL_t set_motor= {0};
	ride_states car_state_is = stop;

	// Resetting Structure Members
	memset(&set_motor, 0, sizeof(set_motor));

	if(gps_car_running.GPS_CAR_DISTANCE_to_destination <= 5)
	{
		car->state = destination_reached;
		return (void *)&set_motor;
	}

	car_state_is = get_direction(left, center, right, rear, gps_car_running);
	switch(car_state_is)
	{
		case go_straight		:set_motor.MOTOR_DRIVE_FORWARD = 1;
						   		 set_motor.MOTOR_DRIVE_SPEED = 5;
						   		 set_motor.MOTOR_STEER_STRAIGHT =1;
						   		 car->state = going_forward; break;

		case go_reverse			:set_motor.MOTOR_DRIVE_REVERSE = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5; //TODO: Set as 5
								 set_motor.MOTOR_STEER_FULL_LEFT =1;
								 car->state = going_reverse;break;

		case stop				:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 0;
								 set_motor.MOTOR_STEER_STRAIGHT =1;
								 car->state = stopped;break;

		case turn_left			:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_FULL_LEFT = 1;break;

		case turn_right			:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_FULL_RIGHT = 1;break;

		case slight_left		:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_SLIGHT_LEFT = 1;break;

		case slight_right		:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_SLIGHT_RIGHT = 1;break;

		case very_slight_right 	:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_VERY_SLIGHT_RIGHT = 1; break;

		case very_slight_left	:set_motor.MOTOR_DRIVE_FORWARD = 1;
		 	 	 	 	 	 	 set_motor.MOTOR_DRIVE_SPEED = 5;
								 set_motor.MOTOR_STEER_VERY_SLIGHT_LEFT = 1; break;

		default 				:set_motor.MOTOR_DRIVE_FORWARD = 1;
								 set_motor.MOTOR_DRIVE_SPEED = 0; //This condition should never happen
	}
	return (void *)(&set_motor);
}
