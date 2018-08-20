/*
 * test_gps.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: krish
 */



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

// Include for C++
using namespace cgreen;

#include "gps_module.h"
//#include "gps_module.cpp"
//#include "i2cMagmtr.h"
//#include "generated_can.h"



Ensure(test_turn_direction)
{
	// Straight = 3
	assert_that(turn_direction(1), is_equal_to(3));
	assert_that(turn_direction(5), is_equal_to(3));

	assert_that(turn_direction(-360), is_equal_to(3));
	assert_that(turn_direction(-358), is_equal_to(3));
	assert_that(turn_direction(-356), is_equal_to(3));

	assert_that(turn_direction(0), is_equal_to(3));
	assert_that(turn_direction(-5), is_equal_to(3));

	assert_that(turn_direction(360), is_equal_to(3));
	assert_that(turn_direction(358), is_equal_to(3));
	assert_that(turn_direction(356), is_equal_to(3));


	//slight left = 2
	assert_that(turn_direction(6), is_equal_to(2));
	assert_that(turn_direction(8), is_equal_to(2));
	assert_that(turn_direction(15), is_equal_to(2));

	assert_that(turn_direction(-355), is_equal_to(2));
	assert_that(turn_direction(-350), is_equal_to(2));
	assert_that(turn_direction(-346), is_equal_to(2));

	//slight right = 4
	assert_that(turn_direction(-6), is_equal_to(4));
	assert_that(turn_direction(-8), is_equal_to(4));
	assert_that(turn_direction(-15), is_equal_to(4));

	assert_that(turn_direction(355), is_equal_to(4));
	assert_that(turn_direction(350), is_equal_to(4));
	assert_that(turn_direction(346), is_equal_to(4));


	//medium left = 1
	assert_that(turn_direction(16), is_equal_to(1));
	assert_that(turn_direction(45), is_equal_to(1));
	assert_that(turn_direction(60), is_equal_to(1));

	assert_that(turn_direction(-345), is_equal_to(1));
	assert_that(turn_direction(-325), is_equal_to(1));
	assert_that(turn_direction(-301), is_equal_to(1));

	//medium right = 5
	assert_that(turn_direction(-16), is_equal_to(5));
	assert_that(turn_direction(-45), is_equal_to(5));
	assert_that(turn_direction(-60), is_equal_to(5));

	assert_that(turn_direction(345), is_equal_to(5));
	assert_that(turn_direction(325), is_equal_to(5));
	assert_that(turn_direction(301), is_equal_to(5));


	// full left = 0
	assert_that(turn_direction(61), is_equal_to(0));
	assert_that(turn_direction(120), is_equal_to(0));
	assert_that(turn_direction(180), is_equal_to(0));

	assert_that(turn_direction(-300), is_equal_to(0));
	assert_that(turn_direction(-250), is_equal_to(0));
	assert_that(turn_direction(-181), is_equal_to(0));

	// full right = 6
	assert_that(turn_direction(-61), is_equal_to(6));
	assert_that(turn_direction(-120), is_equal_to(6));
	assert_that(turn_direction(-180), is_equal_to(6));

	assert_that(turn_direction(300), is_equal_to(6));
	assert_that(turn_direction(250), is_equal_to(6));
	assert_that(turn_direction(181), is_equal_to(6));

	// stop = 7
	assert_that(turn_direction(-361), is_equal_to(7));
	assert_that(turn_direction(361), is_equal_to(7));

}


TestSuite *gps_suite()
{
    TestSuite *suite = create_test_suite();
    add_test(suite, test_turn_direction);

    return suite;
}
