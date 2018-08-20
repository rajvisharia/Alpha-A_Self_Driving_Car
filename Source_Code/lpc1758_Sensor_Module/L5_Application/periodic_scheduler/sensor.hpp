/*
 * sensor.hpp
 *
 *  Created on: Oct 20, 2017
 *      Author: sushm
 */

#ifndef SENSOR_HPP_
#define SENSOR_HPP_
#include "gpio.hpp"
#include "stdio.h"
#include <stdint.h>
#include "LPC17xx.h"

//middle intr 2_0; rx P1_19
//right intr 2_1; rx P1_20
//left intr 2_2; rx P1_22
//back intr 2_3; rx P1_23


typedef enum{
    middle,
    left,
    right,
    back,
}sensr;


class sensor
{
public:
    uint64_t start;
    uint64_t stop;
    uint32_t distance;
    uint32_t old;
    bool wakeup;
    sensr loc;
    sensor();
    sensor(sensr loc);
    void powerUpDelay();
    void commandRanging();
    void enableFEdge(void (*fptr1) (void));
    void calculateDistance(sensr which);
};

#endif /* SENSOR_HPP_ */
