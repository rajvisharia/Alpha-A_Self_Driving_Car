/*
 * point.h
 *
 *  Created on: Oct 31, 2017
 *      Author: sushm
 */

#ifndef L5_APPLICATION_SOURCE_POINT_H_
#define L5_APPLICATION_SOURCE_POINT_H_


class Point
{
public:
	Point() : x(0), y(0) {}
	Point(double lat, double lon) : x(lat), y(lon) {}

	double x;
	double y;
};



#endif /* L5_APPLICATION_SOURCE_POINT_H_ */
