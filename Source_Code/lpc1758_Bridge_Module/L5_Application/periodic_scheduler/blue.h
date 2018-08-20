/*

 * blue.h
 *
 *  Created on: Nov 13, 2017
 *      Author: Kathan Patel
*/


#ifndef L5_APPLICATION_PERIODIC_SCHEDULER_BLUE_H_
#define L5_APPLICATION_PERIODIC_SCHEDULER_BLUE_H_

#include<iostream>
#include <string>
//#include <string.h>
#include <stdlib.h>
#include<periodic_scheduler/periodic_callback.h>

using namespace std;


    int validate_store(char c[]);
    bool validate_latitude(string temp);
    bool validate_longitude(string temp);
    bool validate_checkpoint(string temp);

        //getter    functions
    int get_startstop();
    double get_latitude(int index);
    double get_longitude(int index);
    int get_checkpoints();

#endif //L5_APPLICATION_PERIODIC_SCHEDULER_BLUE_H_

