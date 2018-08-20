/*
 * test_driverData.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: Admin
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

// Include for C++
using namespace cgreen;
#include "motors_module.h"
#include "generated_can.h"

Ensure(test_servo_motor_steer_angle)
{
    assert_that(servo_motor_steer_angle(full_left_dir, 10.0), is_equal_to(0));
    assert_that(servo_motor_steer_angle(full_left_dir, 10.1), is_equal_to(1));
    assert_that(servo_motor_steer_angle(full_left_dir, 10.2), is_equal_to(0));

    assert_that(servo_motor_steer_angle(straight_dir, 15.3), is_equal_to(0));
    assert_that(servo_motor_steer_angle(straight_dir, 15.4), is_equal_to(1));
    assert_that(servo_motor_steer_angle(straight_dir, 15.5), is_equal_to(0));

    assert_that(servo_motor_steer_angle(slt_left_dir, 13.2), is_equal_to(0));
    assert_that(servo_motor_steer_angle(slt_left_dir, 13.3), is_equal_to(1));
    assert_that(servo_motor_steer_angle(slt_left_dir, 13.4), is_equal_to(0));

    assert_that(servo_motor_steer_angle(slt_right_dir, 17.4), is_equal_to(0));
    assert_that(servo_motor_steer_angle(slt_right_dir, 17.5), is_equal_to(1));
    assert_that(servo_motor_steer_angle(slt_right_dir, 17.6), is_equal_to(0));

    assert_that(servo_motor_steer_angle(full_right_dir, 19.7), is_equal_to(0));
    assert_that(servo_motor_steer_angle(full_right_dir, 19.8), is_equal_to(1));
    assert_that(servo_motor_steer_angle(full_right_dir, 19.9), is_equal_to(0));

}

Ensure(test_dc_motor_drive)
{
    assert_that(dc_motor_drive(forward_drive,17.09), is_equal_to(0));
    assert_that(dc_motor_drive(forward_drive,17.10), is_equal_to(1));
    assert_that(dc_motor_drive(forward_drive,17.11), is_equal_to(0));

    assert_that(dc_motor_drive(forward_drive,17.15), is_equal_to(0));
    assert_that(dc_motor_drive(forward_drive,17.16), is_equal_to(1));
    assert_that(dc_motor_drive(forward_drive,17.17), is_equal_to(0));

    assert_that(dc_motor_drive(forward_drive,17.25), is_equal_to(0));
    assert_that(dc_motor_drive(forward_drive,17.26), is_equal_to(1));
    assert_that(dc_motor_drive(forward_drive,17.27), is_equal_to(0));

    assert_that(dc_motor_drive(forward_drive,17.32), is_equal_to(0));
    assert_that(dc_motor_drive(forward_drive,17.33), is_equal_to(1));
    assert_that(dc_motor_drive(forward_drive,17.34), is_equal_to(0));

    assert_that(dc_motor_drive(neutral_drive,14.9), is_equal_to(0));
    assert_that(dc_motor_drive(neutral_drive,15), is_equal_to(1));
    assert_that(dc_motor_drive(neutral_drive,15.1), is_equal_to(0));

    assert_that(dc_motor_drive(reverse_drive,9.9), is_equal_to(0));
    assert_that(dc_motor_drive(reverse_drive,10), is_equal_to(1));
    assert_that(dc_motor_drive(reverse_drive,10.1), is_equal_to(0));
}

TestSuite* test_motors_module()
{
    TestSuite* suite = create_test_suite();
    add_test(suite, test_servo_motor_steer_angle);
    add_test(suite, test_dc_motor_drive);

    return suite;
}


