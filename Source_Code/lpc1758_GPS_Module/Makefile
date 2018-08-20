# Compiler flags
CXX = g++
CXXFLAGS = -Wall -g

# Points to the root of cgreen test files
CGREEN_DIR = ../../../cgreen

# Google Test headers
CGREEN_HEADERS = -I$(CGREEN_DIR)/include -I$(CGREEN_DIR)/include/cgreen/internal

# External cgreen library and where it's located
LIBS = -L$(CGREEN_DIR) -lcgreen

# Where to place your unit test code
UT_DIR = test_codes

# Example directory
EXAMPLE_DIR = L5_Application

# SJSU Project file directories
PROJ_DIR = ../lpc1758_GPS_Module
HEADER_DIR = -I$(PROJ_DIR)/_can_dbc \
               -I$(PROJ_DIR)/L0_LowLevel \
               -I$(PROJ_DIR)/L1_FreeRTOS \
               -I$(PROJ_DIR)/L1_FreeRTOS/include \
               -I$(PROJ_DIR)/L1_FreeRTOS/hooks \
               -I$(PROJ_DIR)/L1_FreeRTOS/MemMang \
               -I$(PROJ_DIR)/L1_FreeRTOS/portable \
               -I$(PROJ_DIR)/L1_FreeRTOS/portable/mpu \
               -I$(PROJ_DIR)/L2_Drivers/base \
               -I$(PROJ_DIR)/L3_Utils \
               -I$(PROJ_DIR)/L3_Utils/tlm \
               -I$(PROJ_DIR)/L4_IO \
               -I$(PROJ_DIR)/L4_IO/fat \
               -I$(PROJ_DIR)/L4_IO/fat/disk \
               -I$(PROJ_DIR)/L4_IO/fat/option \
               -I$(PROJ_DIR)/L4_IO/wireless \
               -I$(PROJ_DIR)/L5_Application \
               -I$(PROJ_DIR)/L5_Application/examples \
               -I$(PROJ_DIR)/L5_Application/source \
               -I$(PROJ_DIR)/L5_Application/periodic_scheduler \
               -I$(EXAMPLE_DIR) \
			   -I$(PROJ_DIR)\-
			   
# Default for "make"
all : test_all

clean :
	rm -f test_all *.o

test_main.o: $(UT_DIR)/test_main.cpp
	$(CXX) $(CGREEN_HEADERS) $(HEADER_DIR) $(CXXFLAGS) -c $(UT_DIR)/test_main.cpp $(LIBS)

gps_module.o: $(PROJ_DIR)/L5_Application/source/gps_module.cpp
	$(CXX) $(CGREEN_HEADERS) $(HEADER_DIR) $(CXXFLAGS) -c $(PROJ_DIR)/L5_Application/source/gps_module.cpp $(LIBS)

test_gps_module.o: $(UT_DIR)/test_gps_module.cpp gps_module.o
	$(CXX) $(CGREEN_HEADERS) $(HEADER_DIR) $(CXXFLAGS) -c $(UT_DIR)/test_gps_module.cpp $(LIBS)

test_all: test_main.o gps_module.o
	$(CXX) $(CGREEN_HEADERS) $(HEADER_DIR) $(CXXFLAGS) $^ -o $@ $(LIBS)
