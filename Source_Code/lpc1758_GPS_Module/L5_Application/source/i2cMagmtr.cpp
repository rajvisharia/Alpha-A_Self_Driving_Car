/*
 * i2cMagmtr.cpp
 *
 *  Created on: Nov 4, 2017
 *      Author: sushm
 */
#include "i2cMagmtr.h"
#include "i2c2.hpp"
#include "printf_lib.h"
#include "math.h"
#include "utilities.h"

i2cMagmtr::i2cMagmtr() {

}


//static int min_x=100000, max_x = 0000, min_y = 100000, max_y, min_z, max_z;
bool i2cMagmtr::getData(uint16_t &HV){

	uint8_t hv[2];

	//I2C2::getInstance().writeReg(0x3C, 0x01, 0x01);
	I2C2::getInstance().readRegisters(0xC0, 0x02, &hv[0], 1);
	I2C2::getInstance().readRegisters(0xC0, 0x03, &hv[1], 1);
	HV=((hv[0]<<8)+hv[1]);
	return true;
}

//bool i2cMagmtr::getData(int &HV){
//
//	uint8_t hv[2];
//
//	//I2C2::getInstance().writeReg(0x3C, 0x01, 0x01);
//	I2C2::getInstance().readRegisters(0xC0, 0x02, &hv[0], 1);
//	I2C2::getInstance().readRegisters(0xC0, 0x03, &hv[1], 1);
//	HV=((hv[0]<<8)+hv[1]);
//	return true;
//}

void i2cMagmtr::calibrate()
{
	uint8_t byte_0 = 0xf0;
	uint8_t byte_1 = 0xf5;
	uint8_t byte_2 = 0xf6;
	I2C2::getInstance().writeRegisters(0xC0, 0x00, &byte_0, 1);
	//u0_dbg_printf("jj");
	delay_ms(20);
	I2C2::getInstance().writeRegisters(0xC0, 0x00, &byte_1, 1);
	delay_ms(20);
	I2C2::getInstance().writeRegisters(0xC0, 0x00, &byte_2, 1);
	delay_ms(20);

}

void i2cMagmtr::calibrate_stop()
{
	uint8_t byte_2 = 0xf8;
	I2C2::getInstance().writeRegisters(0xC0, 0x00, &byte_2, 1);
	delay_ms(20);
}
