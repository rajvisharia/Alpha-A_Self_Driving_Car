/*
 * i2cMagmtr.h
 *
 *  Created on: Nov 4, 2017
 *      Author: sushm
 */

#ifndef L5_APPLICATION_PERIODIC_SCHEDULER_I2CMAGMTR_H_
#define L5_APPLICATION_PERIODIC_SCHEDULER_I2CMAGMTR_H_
#include <stdint.h>

class i2cMagmtr {
public:
	i2cMagmtr();
	bool getData(uint16_t &Z);
	//bool getData(int &Z);
	void calibrate();
	void calibrate_stop();
};

#endif /* L5_APPLICATION_PERIODIC_SCHEDULER_I2CMAGMTR_H_ */
