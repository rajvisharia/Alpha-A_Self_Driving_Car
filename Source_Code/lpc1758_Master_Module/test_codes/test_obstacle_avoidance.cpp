/*
 * test_obstacle_avoidance.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: Jigar
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

// Include for C++
using namespace cgreen;
#include "obstacle_avoidance.h"
#include "generated_can.h"


Ensure(test_get_left_state)
{
	//Assertions of all equal values
    assert_that(get_left_state(-1), is_equal_to(28));
    assert_that(get_left_state(0), is_equal_to(25));
    assert_that(get_left_state(1), is_equal_to(25));
    assert_that(get_left_state(10), is_equal_to(25));
    assert_that(get_left_state(19), is_equal_to(25));
    assert_that(get_left_state(20), is_equal_to(25));
    assert_that(get_left_state(21), is_equal_to(26));
    assert_that(get_left_state(22), is_equal_to(26));
    assert_that(get_left_state(30), is_equal_to(26));
    assert_that(get_left_state(44), is_equal_to(26));
    assert_that(get_left_state(45), is_equal_to(26));
    assert_that(get_left_state(46), is_equal_to(27));
    assert_that(get_left_state(50), is_equal_to(27));
    assert_that(get_left_state(68), is_equal_to(27));
    assert_that(get_left_state(109), is_equal_to(27));
    assert_that(get_left_state(110), is_equal_to(27));
    assert_that(get_left_state(111), is_equal_to(28));
    assert_that(get_left_state(200), is_equal_to(28));
    assert_that(get_left_state(23423), is_equal_to(28));
    //Assertions of all not equal values
    assert_that(get_left_state(0), is_not_equal_to(26));
    assert_that(get_left_state(0), is_not_equal_to(27));
    assert_that(get_left_state(0), is_not_equal_to(28));

    assert_that(get_left_state(1), is_not_equal_to(26));
    assert_that(get_left_state(1), is_not_equal_to(27));
    assert_that(get_left_state(1), is_not_equal_to(28));

    assert_that(get_left_state(10), is_not_equal_to(26));
    assert_that(get_left_state(10), is_not_equal_to(27));
    assert_that(get_left_state(10), is_not_equal_to(28));

    assert_that(get_left_state(19), is_not_equal_to(26));
    assert_that(get_left_state(19), is_not_equal_to(27));
    assert_that(get_left_state(19), is_not_equal_to(28));

    assert_that(get_left_state(20), is_not_equal_to(26));
    assert_that(get_left_state(20), is_not_equal_to(27));
    assert_that(get_left_state(20), is_not_equal_to(28));

    assert_that(get_left_state(21), is_not_equal_to(25));
    assert_that(get_left_state(21), is_not_equal_to(27));
    assert_that(get_left_state(21), is_not_equal_to(28));

    assert_that(get_left_state(22), is_not_equal_to(25));
    assert_that(get_left_state(22), is_not_equal_to(27));
    assert_that(get_left_state(22), is_not_equal_to(28));

    assert_that(get_left_state(30), is_not_equal_to(25));
    assert_that(get_left_state(30), is_not_equal_to(27));
    assert_that(get_left_state(30), is_not_equal_to(28));

    assert_that(get_left_state(44), is_not_equal_to(25));
    assert_that(get_left_state(44), is_not_equal_to(27));
    assert_that(get_left_state(44), is_not_equal_to(28));

    assert_that(get_left_state(45), is_not_equal_to(25));
    assert_that(get_left_state(45), is_not_equal_to(27));
    assert_that(get_left_state(45), is_not_equal_to(28));

    assert_that(get_left_state(46), is_not_equal_to(25));
    assert_that(get_left_state(46), is_not_equal_to(26));
    assert_that(get_left_state(46), is_not_equal_to(28));

    assert_that(get_left_state(50), is_not_equal_to(25));
    assert_that(get_left_state(50), is_not_equal_to(26));
    assert_that(get_left_state(50), is_not_equal_to(28));

    assert_that(get_left_state(68), is_not_equal_to(25));
    assert_that(get_left_state(68), is_not_equal_to(26));
    assert_that(get_left_state(68), is_not_equal_to(28));

    assert_that(get_left_state(109), is_not_equal_to(25));
    assert_that(get_left_state(109), is_not_equal_to(26));
    assert_that(get_left_state(109), is_not_equal_to(28));

    assert_that(get_left_state(110), is_not_equal_to(25));
    assert_that(get_left_state(110), is_not_equal_to(26));
    assert_that(get_left_state(110), is_not_equal_to(28));

    assert_that(get_left_state(111), is_not_equal_to(25));
    assert_that(get_left_state(111), is_not_equal_to(26));
    assert_that(get_left_state(111), is_not_equal_to(27));

    assert_that(get_left_state(200), is_not_equal_to(25));
    assert_that(get_left_state(200), is_not_equal_to(26));
    assert_that(get_left_state(200), is_not_equal_to(27));

    assert_that(get_left_state(23423), is_not_equal_to(25));
    assert_that(get_left_state(23423), is_not_equal_to(26));
    assert_that(get_left_state(23423), is_not_equal_to(27));

}
Ensure(test_get_right_state)
{
	//Assertions of all equal values
    assert_that(get_right_state(-1), is_equal_to(28));
    assert_that(get_right_state(0), is_equal_to(25));
    assert_that(get_right_state(1), is_equal_to(25));
    assert_that(get_right_state(10), is_equal_to(25));
    assert_that(get_right_state(19), is_equal_to(25));
    assert_that(get_right_state(20), is_equal_to(25));
    assert_that(get_right_state(21), is_equal_to(26));
    assert_that(get_right_state(22), is_equal_to(26));
    assert_that(get_right_state(30), is_equal_to(26));
    assert_that(get_right_state(44), is_equal_to(26));
    assert_that(get_right_state(45), is_equal_to(26));
    assert_that(get_right_state(46), is_equal_to(27));
    assert_that(get_right_state(50), is_equal_to(27));
    assert_that(get_right_state(68), is_equal_to(27));
    assert_that(get_right_state(109), is_equal_to(27));
    assert_that(get_right_state(110), is_equal_to(27));
    assert_that(get_right_state(111), is_equal_to(28));
    assert_that(get_right_state(200), is_equal_to(28));
    assert_that(get_right_state(23423), is_equal_to(28));
    //Assertions of all not equal values
    assert_that(get_right_state(0), is_not_equal_to(26));
    assert_that(get_right_state(0), is_not_equal_to(27));
    assert_that(get_right_state(0), is_not_equal_to(28));

    assert_that(get_right_state(1), is_not_equal_to(26));
    assert_that(get_right_state(1), is_not_equal_to(27));
    assert_that(get_right_state(1), is_not_equal_to(28));

    assert_that(get_right_state(10), is_not_equal_to(26));
    assert_that(get_right_state(10), is_not_equal_to(27));
    assert_that(get_right_state(10), is_not_equal_to(28));

    assert_that(get_right_state(19), is_not_equal_to(26));
    assert_that(get_right_state(19), is_not_equal_to(27));
    assert_that(get_right_state(19), is_not_equal_to(28));

    assert_that(get_right_state(20), is_not_equal_to(26));
    assert_that(get_right_state(20), is_not_equal_to(27));
    assert_that(get_right_state(20), is_not_equal_to(28));

    assert_that(get_right_state(21), is_not_equal_to(25));
    assert_that(get_right_state(21), is_not_equal_to(27));
    assert_that(get_right_state(21), is_not_equal_to(28));

    assert_that(get_right_state(22), is_not_equal_to(25));
    assert_that(get_right_state(22), is_not_equal_to(27));
    assert_that(get_right_state(22), is_not_equal_to(28));

    assert_that(get_right_state(30), is_not_equal_to(25));
    assert_that(get_right_state(30), is_not_equal_to(27));
    assert_that(get_right_state(30), is_not_equal_to(28));

    assert_that(get_right_state(44), is_not_equal_to(25));
    assert_that(get_right_state(44), is_not_equal_to(27));
    assert_that(get_right_state(44), is_not_equal_to(28));

    assert_that(get_right_state(45), is_not_equal_to(25));
    assert_that(get_right_state(45), is_not_equal_to(27));
    assert_that(get_right_state(45), is_not_equal_to(28));

    assert_that(get_right_state(46), is_not_equal_to(25));
    assert_that(get_right_state(46), is_not_equal_to(26));
    assert_that(get_right_state(46), is_not_equal_to(28));

    assert_that(get_right_state(50), is_not_equal_to(25));
    assert_that(get_right_state(50), is_not_equal_to(26));
    assert_that(get_right_state(50), is_not_equal_to(28));

    assert_that(get_right_state(68), is_not_equal_to(25));
    assert_that(get_right_state(68), is_not_equal_to(26));
    assert_that(get_right_state(68), is_not_equal_to(28));

    assert_that(get_right_state(109), is_not_equal_to(25));
    assert_that(get_right_state(109), is_not_equal_to(26));
    assert_that(get_right_state(109), is_not_equal_to(28));

    assert_that(get_right_state(110), is_not_equal_to(25));
    assert_that(get_right_state(110), is_not_equal_to(26));
    assert_that(get_right_state(110), is_not_equal_to(28));

    assert_that(get_right_state(111), is_not_equal_to(25));
    assert_that(get_right_state(111), is_not_equal_to(26));
    assert_that(get_right_state(111), is_not_equal_to(27));

    assert_that(get_right_state(200), is_not_equal_to(25));
    assert_that(get_right_state(200), is_not_equal_to(26));
    assert_that(get_right_state(200), is_not_equal_to(27));

    assert_that(get_right_state(23423), is_not_equal_to(25));
    assert_that(get_right_state(23423), is_not_equal_to(26));
    assert_that(get_right_state(23423), is_not_equal_to(27));

}
Ensure(test_get_center_state)
{
//Assertions of all equal values
assert_that(get_center_state(-1), is_equal_to(28));
assert_that(get_center_state(0), is_equal_to(25));
assert_that(get_center_state(1), is_equal_to(25));
assert_that(get_center_state(10), is_equal_to(25));
assert_that(get_center_state(39), is_equal_to(25));
assert_that(get_center_state(40), is_equal_to(25));
assert_that(get_center_state(41), is_equal_to(26));
assert_that(get_center_state(42), is_equal_to(26));
assert_that(get_center_state(60), is_equal_to(26));
assert_that(get_center_state(79), is_equal_to(26));
assert_that(get_center_state(80), is_equal_to(26));
assert_that(get_center_state(81), is_equal_to(27));
assert_that(get_center_state(90), is_equal_to(27));
assert_that(get_center_state(120), is_equal_to(27));
assert_that(get_center_state(179), is_equal_to(27));
assert_that(get_center_state(180), is_equal_to(27));
assert_that(get_center_state(181), is_equal_to(28));
assert_that(get_center_state(200), is_equal_to(28));
assert_that(get_center_state(23423), is_equal_to(28));
//Assertions of all not equal values
assert_that(get_center_state(0), is_not_equal_to(26));
assert_that(get_center_state(0), is_not_equal_to(27));
assert_that(get_center_state(0), is_not_equal_to(28));

assert_that(get_center_state(1), is_not_equal_to(26));
assert_that(get_center_state(1), is_not_equal_to(27));
assert_that(get_center_state(1), is_not_equal_to(28));

assert_that(get_center_state(10), is_not_equal_to(26));
assert_that(get_center_state(10), is_not_equal_to(27));
assert_that(get_center_state(10), is_not_equal_to(28));

assert_that(get_center_state(39), is_not_equal_to(26));
assert_that(get_center_state(39), is_not_equal_to(27));
assert_that(get_center_state(39), is_not_equal_to(28));

assert_that(get_center_state(40), is_not_equal_to(26));
assert_that(get_center_state(40), is_not_equal_to(27));
assert_that(get_center_state(40), is_not_equal_to(28));

assert_that(get_center_state(41), is_not_equal_to(25));
assert_that(get_center_state(41), is_not_equal_to(27));
assert_that(get_center_state(41), is_not_equal_to(28));

assert_that(get_center_state(42), is_not_equal_to(25));
assert_that(get_center_state(42), is_not_equal_to(27));
assert_that(get_center_state(42), is_not_equal_to(28));

assert_that(get_center_state(60), is_not_equal_to(25));
assert_that(get_center_state(60), is_not_equal_to(27));
assert_that(get_center_state(60), is_not_equal_to(28));

assert_that(get_center_state(79), is_not_equal_to(25));
assert_that(get_center_state(79), is_not_equal_to(27));
assert_that(get_center_state(79), is_not_equal_to(28));

assert_that(get_center_state(80), is_not_equal_to(25));
assert_that(get_center_state(80), is_not_equal_to(27));
assert_that(get_center_state(80), is_not_equal_to(28));

assert_that(get_center_state(81), is_not_equal_to(25));
assert_that(get_center_state(81), is_not_equal_to(26));
assert_that(get_center_state(81), is_not_equal_to(28));

assert_that(get_center_state(90), is_not_equal_to(25));
assert_that(get_center_state(90), is_not_equal_to(26));
assert_that(get_center_state(90), is_not_equal_to(28));

assert_that(get_center_state(120), is_not_equal_to(25));
assert_that(get_center_state(120), is_not_equal_to(26));
assert_that(get_center_state(120), is_not_equal_to(28));

assert_that(get_center_state(179), is_not_equal_to(25));
assert_that(get_center_state(179), is_not_equal_to(26));
assert_that(get_center_state(179), is_not_equal_to(28));

assert_that(get_center_state(180), is_not_equal_to(25));
assert_that(get_center_state(180), is_not_equal_to(26));
assert_that(get_center_state(180), is_not_equal_to(28));

assert_that(get_center_state(181), is_not_equal_to(25));
assert_that(get_center_state(181), is_not_equal_to(26));
assert_that(get_center_state(181), is_not_equal_to(27));

assert_that(get_center_state(200), is_not_equal_to(25));
assert_that(get_center_state(200), is_not_equal_to(26));
assert_that(get_center_state(200), is_not_equal_to(27));

assert_that(get_center_state(23423), is_not_equal_to(25));
assert_that(get_center_state(23423), is_not_equal_to(26));
assert_that(get_center_state(23423), is_not_equal_to(27));

}

Ensure(test_get_rear_state)
{
//Assertions of all equal values
assert_that(get_rear_state(-1), is_equal_to(28));
assert_that(get_rear_state(0), is_equal_to(25));
assert_that(get_rear_state(1), is_equal_to(25));
assert_that(get_rear_state(10), is_equal_to(25));
assert_that(get_rear_state(39), is_equal_to(25));
assert_that(get_rear_state(40), is_equal_to(25));
assert_that(get_rear_state(41), is_equal_to(26));
assert_that(get_rear_state(42), is_equal_to(26));
assert_that(get_rear_state(60), is_equal_to(26));
assert_that(get_rear_state(79), is_equal_to(26));
assert_that(get_rear_state(80), is_equal_to(26));
assert_that(get_rear_state(81), is_equal_to(27));
assert_that(get_rear_state(90), is_equal_to(27));
assert_that(get_rear_state(120), is_equal_to(27));
assert_that(get_rear_state(179), is_equal_to(27));
assert_that(get_rear_state(180), is_equal_to(27));
assert_that(get_rear_state(181), is_equal_to(28));
assert_that(get_rear_state(200), is_equal_to(28));
assert_that(get_rear_state(23423), is_equal_to(28));
//Assertions of all not equal values
assert_that(get_rear_state(0), is_not_equal_to(26));
assert_that(get_rear_state(0), is_not_equal_to(27));
assert_that(get_rear_state(0), is_not_equal_to(28));

assert_that(get_rear_state(1), is_not_equal_to(26));
assert_that(get_rear_state(1), is_not_equal_to(27));
assert_that(get_rear_state(1), is_not_equal_to(28));

assert_that(get_rear_state(10), is_not_equal_to(26));
assert_that(get_rear_state(10), is_not_equal_to(27));
assert_that(get_rear_state(10), is_not_equal_to(28));

assert_that(get_rear_state(39), is_not_equal_to(26));
assert_that(get_rear_state(39), is_not_equal_to(27));
assert_that(get_rear_state(39), is_not_equal_to(28));

assert_that(get_rear_state(40), is_not_equal_to(26));
assert_that(get_rear_state(40), is_not_equal_to(27));
assert_that(get_rear_state(40), is_not_equal_to(28));

assert_that(get_rear_state(41), is_not_equal_to(25));
assert_that(get_rear_state(41), is_not_equal_to(27));
assert_that(get_rear_state(41), is_not_equal_to(28));

assert_that(get_rear_state(42), is_not_equal_to(25));
assert_that(get_rear_state(42), is_not_equal_to(27));
assert_that(get_rear_state(42), is_not_equal_to(28));

assert_that(get_rear_state(60), is_not_equal_to(25));
assert_that(get_rear_state(60), is_not_equal_to(27));
assert_that(get_rear_state(60), is_not_equal_to(28));

assert_that(get_rear_state(79), is_not_equal_to(25));
assert_that(get_rear_state(79), is_not_equal_to(27));
assert_that(get_rear_state(79), is_not_equal_to(28));

assert_that(get_rear_state(80), is_not_equal_to(25));
assert_that(get_rear_state(80), is_not_equal_to(27));
assert_that(get_rear_state(80), is_not_equal_to(28));

assert_that(get_rear_state(81), is_not_equal_to(25));
assert_that(get_rear_state(81), is_not_equal_to(26));
assert_that(get_rear_state(81), is_not_equal_to(28));

assert_that(get_rear_state(90), is_not_equal_to(25));
assert_that(get_rear_state(90), is_not_equal_to(26));
assert_that(get_rear_state(90), is_not_equal_to(28));

assert_that(get_rear_state(120), is_not_equal_to(25));
assert_that(get_rear_state(120), is_not_equal_to(26));
assert_that(get_rear_state(120), is_not_equal_to(28));

assert_that(get_rear_state(179), is_not_equal_to(25));
assert_that(get_rear_state(179), is_not_equal_to(26));
assert_that(get_rear_state(179), is_not_equal_to(28));

assert_that(get_rear_state(180), is_not_equal_to(25));
assert_that(get_rear_state(180), is_not_equal_to(26));
assert_that(get_rear_state(180), is_not_equal_to(28));

assert_that(get_rear_state(181), is_not_equal_to(25));
assert_that(get_rear_state(181), is_not_equal_to(26));
assert_that(get_rear_state(181), is_not_equal_to(27));

assert_that(get_rear_state(200), is_not_equal_to(25));
assert_that(get_rear_state(200), is_not_equal_to(26));
assert_that(get_rear_state(200), is_not_equal_to(27));

assert_that(get_rear_state(23423), is_not_equal_to(25));
assert_that(get_rear_state(23423), is_not_equal_to(26));
assert_that(get_rear_state(23423), is_not_equal_to(27));

}

Ensure(test_get_rear_status)
{
	assert_that(get_rear_status(too_near), is_equal_to(stop));
	assert_that(get_rear_status(far), is_equal_to(go_reverse));
	assert_that(get_rear_status(too_far), is_equal_to(go_reverse));
	assert_that(get_rear_status(near), is_equal_to(go_reverse));
}

Ensure(test_get_turn_status)
{
	/*assert_that(get_turn_status(too_near, too_near, too_near), is_equal_to(stop));
	assert_that(get_turn_status(too_near, too_near, too_far), is_equal_to(go_reverse));
	assert_that(get_turn_status(too_near, too_far, too_near), is_equal_to(turn_right));
	assert_that(get_turn_status(too_near, too_far, too_far), is_equal_to(turn_right));
	assert_that(get_turn_status(too_far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_turn_status(too_far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_turn_status(too_far, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_turn_status(too_far, too_far, too_far), is_equal_to(go_straight));

	assert_that(get_turn_status(near, near, too_far), is_equal_to(go_straight));
	assert_that(get_turn_status(near, near, too_near), is_equal_to(go_straight));
	*/
	//Reverse condition
	assert_that(get_turn_status(too_near, too_near, too_near), is_equal_to(stop));
	assert_that(get_turn_status(too_near, too_near, near), is_equal_to(go_reverse));
	assert_that(get_turn_status(too_near, too_near, far), is_equal_to(go_reverse));
	assert_that(get_turn_status(too_near, too_near, too_far), is_equal_to(go_reverse));

	//Turn Right
	assert_that(get_turn_status(too_near, near, far), is_equal_to(turn_right));
	assert_that(get_turn_status(too_near, far, far), is_equal_to(turn_right));
	assert_that(get_turn_status(too_near, too_far, far), is_equal_to(turn_right));

	//Slight Right
	assert_that(get_turn_status(near, near, far), is_equal_to(go_straight));
	assert_that(get_turn_status(near, far, far), is_equal_to(slight_right));
	assert_that(get_turn_status(near, too_far, far), is_equal_to(slight_right));

	//Turn Left
	assert_that(get_turn_status(near, too_near,  far), is_equal_to(turn_left));
	assert_that(get_turn_status(far, too_near, far), is_equal_to(turn_left));
	assert_that(get_turn_status(too_far, too_near, far), is_equal_to(turn_left));

	//Slight left
	assert_that(get_turn_status(near, near,  far), is_equal_to(go_straight));
	assert_that(get_turn_status(far, near, far), is_equal_to(slight_left));
	assert_that(get_turn_status(too_far, near, far), is_equal_to(slight_left));

	//Else go straight condition

	assert_that(get_turn_status(far, far, too_far), is_equal_to(go_straight));
	assert_that(get_turn_status(far, too_far, too_near), is_equal_to(go_straight));

}

Ensure(test_get_direction)
{
	/*//Turn Right Test Cases
	assert_that(get_direction(too_near, near, near, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, near, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, near, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, near, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, near, far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, far, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, near, too_far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, too_far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, too_far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, near, too_far, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, far, near, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, near, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, near, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, near, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, far, far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, far, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, far, too_far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, too_far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, too_far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, far, too_far, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, too_far, near, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, near, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, near, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, near, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, too_far, far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, far, far), is_equal_to(turn_right));

	assert_that(get_direction(too_near, too_far, too_far, too_near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, too_far, near), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, too_far, too_far), is_equal_to(turn_right));
	assert_that(get_direction(too_near, too_far, too_far, far), is_equal_to(turn_right));

	//Turn Left Test Cases
	assert_that(get_direction(near, near, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(near, near, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(near, near, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(near, near, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(far, near, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(far, near, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(far, near, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(far, near, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(too_far, near, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, near, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, near, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(too_far, near, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(near, far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(near, far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(near, far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(near, far, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(far, far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(far, far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(far, far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(far, far, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(too_far, far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(too_far, far, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(near, too_far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(near, too_far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(near, too_far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(near, too_far, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(far, too_far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(far, too_far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(far, too_far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(far, too_far, too_near, far), is_equal_to(turn_left));

	assert_that(get_direction(too_far, too_far, too_near, too_near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, too_far, too_near, near), is_equal_to(turn_left));
	assert_that(get_direction(too_far, too_far, too_near, too_far), is_equal_to(turn_left));
	assert_that(get_direction(too_far, too_far, too_near, far), is_equal_to(turn_left));

	//Go_streight Test Cases
	assert_that(get_direction(near, near, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, near, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, near, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, far, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, too_far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, too_far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(near, too_far, too_far, too_near), is_equal_to(go_straight));

	assert_that(get_direction(far, near, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, near, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, near, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, far, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, too_far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, too_far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(far, too_far, too_far, too_near), is_equal_to(go_straight));

	assert_that(get_direction(too_far, near, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, near, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, near, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, far, too_far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, too_far, near, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, too_far, far, too_near), is_equal_to(go_straight));
	assert_that(get_direction(too_far, too_far, too_far, too_near), is_equal_to(go_straight));

	// Stop Test Cases
	assert_that(get_direction(too_near, too_near, too_near, too_near), is_equal_to(stop));

	assert_that(get_direction(too_near, far, too_near, too_near), is_equal_to(stop));
	assert_that(get_direction(too_near, near, too_near, too_near), is_equal_to(stop));
	assert_that(get_direction(too_near, too_far, too_near, too_near), is_equal_to(stop));

	assert_that(get_direction(too_near, too_near, near, too_near), is_equal_to(stop));
	assert_that(get_direction(too_near, too_near, too_near, too_near), is_equal_to(stop));
	assert_that(get_direction(too_near, too_near, far, too_near), is_equal_to(stop));

	assert_that(get_direction(too_near, too_near, too_near, too_near), is_equal_to(stop));
	assert_that(get_direction(near, too_near, too_near, too_near), is_equal_to(stop));
	assert_that(get_direction(too_far, too_near, too_near, too_near), is_equal_to(stop));

	//Go Reverse Test Cases
	assert_that(get_direction(too_near, too_near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, far, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, far, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_near, too_far, too_far, too_near), is_not_equal_to(go_reverse));

	assert_that(get_direction(near, too_near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, far, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, far, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(near, too_far, too_far, too_near), is_not_equal_to(go_reverse));

	assert_that(get_direction(far, too_near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, far, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, far, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(far, too_far, too_far, too_near), is_not_equal_to(go_reverse));

	assert_that(get_direction(too_far, too_near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, near, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, near, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, near, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, near, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, far, too_far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, far, far, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_far, too_near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_far, near, too_near), is_not_equal_to(go_reverse));
	assert_that(get_direction(too_far, too_far, too_far, too_near), is_not_equal_to(go_reverse));

*/
}

TestSuite* test_obstacle_avoidance()
{
    TestSuite* suite = create_test_suite();
    add_test(suite, test_get_left_state);
    add_test(suite, test_get_right_state);
    add_test(suite, test_get_center_state);
    add_test(suite, test_get_rear_state);
    add_test(suite, test_get_rear_status);
    add_test(suite, test_get_turn_status);
    add_test(suite, test_get_turn_status);
    add_test(suite, test_get_direction);
    return suite;
}
