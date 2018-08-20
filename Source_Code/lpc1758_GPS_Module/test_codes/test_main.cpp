#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

// Include for C++
using namespace cgreen;

// Include other files under test
//#include "test_c_list.c"
#include "test_gps_module.cpp"

int main(int argc, char **argv)
{
  TestSuite *suite = create_test_suite();
  add_suite(suite, gps_suite());
  //add_suite(suite, c_list_suite());

  return run_test_suite(suite, create_text_reporter());
}
