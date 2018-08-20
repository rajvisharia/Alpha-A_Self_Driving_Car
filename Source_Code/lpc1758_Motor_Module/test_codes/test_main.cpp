/*
 * test_main.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: Admin
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "test_main.cpp"

// Include for C++
using namespace cgreen;

// Include other files under test
#include "test_motors_module.cpp"

int main(int argc, char **argv)
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, test_motors_module());

    return run_test_suite(suite, create_text_reporter());
}




