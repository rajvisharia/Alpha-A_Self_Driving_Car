/*
 * gps_module.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: sushm
 */



/*

 * gps_module.cpp

 *

 *  Created on: Oct 25, 2017

 *      Author: krish

 */

#include "gps_module.h"
#include "printf_lib.h"
#include <math.h>


float bearing_angle(float lat1, float long1, float lat2, float long2)
{



float long_diff = long2*3.14159265/180 - long1*3.14159265/180;

float x = cos(lat2*3.14159265/180) * sin(long_diff);

float y = cos(lat1*3.14159265/180) * sin(lat2*3.14159265/180) - sin(lat1*3.14159265/180)*cos(lat2*3.14159265/180)*cos(long_diff);



//double x = sin(90*3.14159265/180);

float bearing = atan2(x,y);


return bearing*180/3.14159265;

}





float distance(float lat1, float long1, float lat2, float long2)
{

	float radius = 6371000;   //in metres



	//converting degrees to radians

	//calculating the diff of latitudes and longitudes

	float long_diff = long2*3.14159265/180 - long1*3.14159265/180;

	float lat_diff = lat2*3.14159265/180 - lat1*3.14159265/180;


	lat1 = lat1*3.14159265/180;

	long1 = long1*3.14159265/180;

	lat2 = lat2*3.14159265/180;

	long2 = long2*3.14159265/180;


	float a = sin(lat_diff/2)*sin(lat_diff/2) + cos(lat1)*cos(lat2)*sin(long_diff/2)*sin(long_diff/2);
	float c = 2*atan2(sqrt(a), sqrt(1-a));
	float distance = radius*c;



	return distance;

}

uint8_t turn_direction(float degree)
{
	  //      0   1   2   3   4   5   6
	  //     fl  ml  sl   s   sr  mr  fr
	uint8_t dir_msg;

	   if((-10 <= degree && degree <= 10) || (-360 <= degree && degree < -350) || (350 < degree && degree <= 360))
	   {
	    dir_msg = 3;  //go straight
	   }
	   else if((10 < degree && degree <= 30) || (-350 <= degree && degree < -330))
	   {
	    dir_msg = 2;   // slight left :   5 degrees
	   }
	   else if((30 < degree && degree <= 60) || (-330 <= degree && degree < -300))
	   {
	    dir_msg = 1;   // mid left : 15 degrees
	   }
	   else if((60 < degree && degree <= 180) || (-300 <= degree && degree < -180))
	   {
	    dir_msg = 0;    // full left : 60 degrees
	   }
	   else if((330 < degree && degree <= 350) || (-30 <= degree && degree < -10))
	   {
	    dir_msg = 4;   // slight right :   5 degrees
	   }
	   else if((300 < degree && degree <= 330) || (-60 <= degree && degree < -30))
	   {
	    dir_msg = 5;   // mid right : 15 degrees
	   }
	   else if((180 < degree && degree <= 300) || (-180 <= degree && degree < -60))
	   {
	    dir_msg = 6;    // full right : 60 degrees
	   }
	   else
	   {
		   u0_dbg_printf("deg: %f\n", degree);
	    dir_msg = 3;    // stop the motors, not able to calaculate correct angle to turn
	   }

	   return dir_msg;
}
