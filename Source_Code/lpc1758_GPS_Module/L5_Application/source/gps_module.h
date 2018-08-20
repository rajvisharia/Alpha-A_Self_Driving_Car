/*
 * gps_module.h
 *
 *  Created on: Oct 31, 2017
 *      Author: sushm
 */

#ifndef L5_APPLICATION_SOURCE_GPS_MODULE_H_
#define L5_APPLICATION_SOURCE_GPS_MODULE_H_

#include <stdint.h>

float bearing_angle(float lat1, float long1, float lat2, float long2);

float distance(float lat1, float long1, float lat2, float long2);

uint8_t turn_direction(float degree);


#endif /* L5_APPLICATION_SOURCE_GPS_MODULE_H_ */
