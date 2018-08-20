#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

// Include for C++
using namespace cgreen;
#include "blue.h"
#include "generated_can.h"

blue bt;

Ensure(test_validate_latitude){
	assert_that(bt.validate_latitude("23.567533"),is_equal_to(true));
	assert_that(bt.validate_latitude("44.864321"),is_equal_to(true));
	assert_that(bt.validate_latitude("-76.823455"),is_equal_to(true));
	assert_that(bt.validate_latitude("-89.876123"),is_equal_to(true));
	assert_that(bt.validate_latitude("-90.000000"),is_equal_to(true));
	assert_that(bt.validate_latitude("90.000000"),is_equal_to(true));
	assert_that(bt.validate_latitude("-92.724353"),is_equal_to(false));
	assert_that(bt.validate_latitude("182.453232"),is_equal_to(false));
	assert_that(bt.validate_latitude("99823.235226"),is_not_equal_to(true));
	assert_that(bt.validate_latitude("-72342.902332"),is_not_equal_to(true));
	assert_that(bt.validate_latitude("0.000000"),is_equal_to(true));
}

Ensure(test_validate_longitude){
	assert_that(bt.validate_longitude("112.635294"), is_not_equal_to(true));
	assert_that(bt.validate_longitude("90.124222"),is_equal_to(true));
	assert_that(bt.validate_longitude("-123.690243"),is_equal_to(true));
	assert_that(bt.validate_longitude("-179.673136"),is_equal_to(true));
	assert_that(bt.validate_longitude("180.000000"),is_equal_to(true));
	assert_that(bt.validate_longitude("-180.000000"),is_equal_to(true));
	assert_that(bt.validate_longitude("-81234.84326"),is_not_equal_to(true));
	assert_that(bt.validate_longitude("98231.90122"),is_equal_to(false));
	assert_that(bt.validate_longitude("-53.62332"),is_equal_to(true));
	assert_that(bt.validate_longitude("-89.087163"),is_not_equal_to(false));
}

//Ensure(test_validate_store){
//
//}

TestSuite* test_blue()
{
    TestSuite* suite = create_test_suite();
    add_test(suite, test_validate_latitude);
    add_test(suite, test_validate_longitude);
//    add_test(suite, test_validate_store);

    return suite;
}
