/*
 * sensor.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: sushm
 */
#include <stdint.h>
#include "io.hpp"
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

GPIO mid(P1_19);//rx triggering
GPIO rt(P1_20);
GPIO lft(P1_22);
GPIO bck(P1_23);

//void read_sensor_fe(void);
sensor::sensor(sensr loc)
{
    start = 0;
    stop = 0;
    distance = 0;
    wakeup = false;
    this->loc = loc;
}

sensor::sensor()
{
    start = 0;
    stop = 0;
    distance = 0;
    wakeup = false;
}

void sensor::powerUpDelay()
{
    if(loc == middle)
    {
        mid.setAsOutput();
        delay_ms(250); //initial delay
        mid.setHigh();
        delay_ms(100); // caliberation and first reading
        mid.setLow();
    }
    else if(loc == left)
    {
        lft.setAsOutput();
        delay_ms(250); //initial delay
        lft.setHigh();
        delay_ms(100); // caliberation and first reading
        lft.setLow();
    }
    else if(loc == right)
    {
        rt.setAsOutput();
        delay_ms(250); //initial delay
        rt.setHigh();
        delay_ms(100); // caliberation and first reading
        rt.setLow();
    }
    else if(loc == back)
    {
        bck.setAsOutput();
        delay_ms(250); //initial delay
        bck.setHigh();
        delay_ms(100); // caliberation and first reading
        bck.setLow();
    }

}
void sensor::commandRanging(void)
{
    if(loc == middle)
    {
        mid.setHigh();
        delay_us(50); //triggering
        mid.setLow();
        start = sys_get_uptime_us(); //start the timer
    }
    else if(loc == left)
    {
        lft.setHigh();
        delay_us(50); //triggering
        lft.setLow();
        start = sys_get_uptime_us(); //start the timer
    }

    else if(loc == right)
    {
        rt.setHigh();
        delay_us(50); //triggering
        rt.setLow();
        start = sys_get_uptime_us(); //start the timer
    }
    else if (loc == back) {
        bck.setHigh();
        delay_us(50); //triggering
        bck.setLow();
        start = sys_get_uptime_us(); //start the timer
    }


}
void sensor::enableFEdge(void (*fptr1) (void))
{
    if(loc == middle)
        eint3_enable_port2(0,eint_falling_edge,fptr1);
    else if(loc == right)
        eint3_enable_port2(1,eint_falling_edge,fptr1);
    else if(loc == left)
        eint3_enable_port2(2,eint_falling_edge,fptr1);
    else if(loc == back)
        eint3_enable_port2(3,eint_falling_edge,fptr1);
}
void sensor::calculateDistance(sensr which)
{
    old = distance;
    stop = sys_get_uptime_us();
    distance= (stop - start)/147;
    if(distance != old && (distance < 60))
    u0_dbg_printf("%d - %d\n",which, distance);
}
