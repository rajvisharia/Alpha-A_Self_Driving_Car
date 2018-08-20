/*
 * motors_module.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: Admin
 */

#include "generated_can.h"
#include "lpc_pwm.hpp"
#include "io.hpp"
#include "gpio.hpp"
#include "utilities.h"
#include "eint.h"


PWM SERVO_MOTOR(PWM::pwm1, 9.915);	// Servo motor on P2.0 and 100Hz.
PWM DC_MOTOR(PWM::pwm2, 100);		// Servo motor on P2.0 and 100Hz

uint8_t rpm = 0;
float sensorspeed = 0.0, error = 0.0, currentspeed = 0.0, old = 0.0;
float pwm = 17.00;
int cnt = 0;


// Speed sensor.
void (*Rfptr) (void);


void read_rising_RPM_fe(void)
{
	rpm++;
}

void speedcontrol(float reqdspeed)
{
	/*
	 *  Speed = (2*pi*r*N) m/sec = (2*pi*r*n*(60*60)) m/hr.
	 *  1 mile = 160934.4 cms.
	 *  d = 2r = 5.6 cms = (5.6 / 160934.4) miles.
	 *  2*pi*r*60*60 = ((2*pi*5.6)*(60*60))/(160934.4) = 0.7867 miles/hr.
	 *  100 = converting from 10ms to sec.
	 *  N = no. of revolutions / no. of magnets = (rpm / 5).
	 */
	sensorspeed = 100 * 0.7867 * (rpm / 5.0);	//miles per hour //TODO
	/*
	 * doubt : 10hz to 100hz
	 * speed should increased by 10
	 */
	error = reqdspeed - sensorspeed; //error +ve when uphill and -ve when downhill

	//u0_dbg_printf("currentspeed %f speed %f Perr : %f\n", currentspeed, speed, error);

	// Increase PWM for Uphill.
	if(error > 0.5)
	{
		DC_MOTOR.set(pwm + (error * 0.25));
	}

	// Decrease PWM for Downhill.
	else if(error < -0.15)
	{
		DC_MOTOR.set(10.1); 		// Brake!!!
	}
	else if(error < -0.10)
	{
		float newpwm = pwm + (error * 0.5);

		if(newpwm > 15.4)
			DC_MOTOR.set(newpwm);
		else
			DC_MOTOR.set(15.4); 			// Min PWM reqd. for motor to run
	}

	rpm = 0;

}


//bool servo_motor_steer_angle (motor_steer direction) // angle data-type to be  fixed
bool servo_motor_steer_angle (MOTOR_SIGNAL_t motor_steer)
{
	if (motor_steer.MOTOR_STEER_FULL_LEFT)
	{
		SERVO_MOTOR.set(10.1);
	}
	else if (motor_steer.MOTOR_STEER_SLIGHT_LEFT)
	{
		SERVO_MOTOR.set(13.3);
	}
	else if (motor_steer.MOTOR_STEER_VERY_SLIGHT_LEFT)
	{
		SERVO_MOTOR.set(14.7);
	}
	else if (motor_steer.MOTOR_STEER_STRAIGHT)
	{
		SERVO_MOTOR.set(15.4);
	}
	else if (motor_steer.MOTOR_STEER_VERY_SLIGHT_RIGHT)
	{
		SERVO_MOTOR.set(16.1);
	}
	else if (motor_steer.MOTOR_STEER_SLIGHT_RIGHT)
	{
		SERVO_MOTOR.set(17.5);
	}
	else if (motor_steer.MOTOR_STEER_FULL_RIGHT)
	{
		SERVO_MOTOR.set(19.8);
	}
	else
	{
		SERVO_MOTOR.set(15.4);
	}

	return true;
}


/*
 *  Function definition for Reverse functionality.
 */
void motor_reverse(int is_init_done)
{
	if(is_init_done < 50)
	{
		DC_MOTOR.set(16.0);
		delay_ms(2);
		DC_MOTOR.set(15.3);
	}
	else
		DC_MOTOR.set(15.3);
}


/*
 *  DC Motor
 */
bool dc_motor_drive_speed (MOTOR_SIGNAL_t motor_drive)
{

	static int is_reverse_init_complete = 0;
	is_reverse_init_complete = (motor_drive.MOTOR_DRIVE_REVERSE) ? is_reverse_init_complete : 0;


	if (motor_drive.MOTOR_DRIVE_SPEED == 0.0)
	{
		cnt = 0;
		currentspeed = 0.0;
		//pwm = 10.1;
		pwm = 15.6;					//pwm changed from 10.1 to 15.6 after reverse added.
		DC_MOTOR.set(pwm);
	}

	else if (motor_drive.MOTOR_DRIVE_SPEED == 5.0 && motor_drive.MOTOR_DRIVE_FORWARD == 1)
	{
		//min = 5.5069 max = 6.2936 avg = 5.90025
		if (currentspeed == 0)
		{
			pwm = 16.85;
			DC_MOTOR.set(pwm);
		}
		currentspeed = 1.7;			//Changed from 2.5

		speedcontrol(currentspeed);
	}

	else if(motor_drive.MOTOR_DRIVE_SPEED == 5.0 && motor_drive.MOTOR_DRIVE_REVERSE == 1)
	{
		if (is_reverse_init_complete < 50)
		{
			is_reverse_init_complete++;
		}
		motor_reverse(is_reverse_init_complete);
	}

	/*
	else if(motor_drive.MOTOR_DRIVE_SPEED == 15.0)
	{
		//min = 7.867 max = 8.653 avg = 8.26
		if(currentspeed == 0)
		{
			pwm = 17.00;
			DC_MOTOR.set(pwm);
		}
		currentspeed = 3.5;
		//	pwm = 17.16;
		//	DC_motor.set(pwm);
		speedcontrol(currentspeed);
	}

	else if (motor_drive.MOTOR_DRIVE_SPEED == 25)
	{
		//min = 8.653 max = 9.44 avg = 9.0465
		currentspeed = 9.0465;
		pwm = 17.33;
		DC_motor.set(17.33);

	 }
	 */

	else
	{
		DC_MOTOR.set(15.6);					// PWM changed from 10.1 to 15.6 after reverse added.
	}

	return true;
}


