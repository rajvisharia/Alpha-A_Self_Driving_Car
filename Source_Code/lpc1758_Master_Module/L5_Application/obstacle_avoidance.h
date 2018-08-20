#ifndef L5_APPLICATION_OBSTACLE_AVOIDANCE_H_
#define L5_APPLICATION_OBSTACLE_AVOIDANCE_H_

#include <stdint.h>
#include <stdbool.h>
#include "Indicators.h"

typedef uint8_t range_type;

typedef enum
{
	too_near       = 25,
	near,
	far,
	too_far,
	no_of_ranges
}distance;

typedef enum
{
	turn_left,
	turn_right,
	go_straight,
	go_reverse,
	stop,
	slight_left,
	slight_right,
	very_slight_right,
	very_slight_left,
	no_of_states
}ride_states;

typedef struct
{
	range_type left_range;
	range_type right_range;
	range_type center_range;
	range_type rear_range;
}dir_range;


uint8_t get_left_state(uint16_t left_rdg);
uint8_t get_right_state(uint16_t right_rdg);
uint8_t get_center_state(uint16_t center_rdg);
uint8_t get_rear_state(uint16_t rear_rdg);

void* set_motor_direction_and_speed(Indicator *cd, range_type left, range_type center, range_type right, range_type rear, GPS_CAR_RUNNING_t gps_car_running);

#endif
