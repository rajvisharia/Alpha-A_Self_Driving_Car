/*
 * Indicator.h
 *
 *  Created on: Dec 10, 2017
 *      Author: Jigar
 */

#ifndef L5_APPLICATION_INDICATORS_H_
#define L5_APPLICATION_INDICATORS_H_


#ifndef L5_APPLICATION_SOURCE_INDICATORS_HPP_
#define L5_APPLICATION_SOURCE_INDICATORS_HPP_

void init_indicator_gpio();
void turn_on_tail_lights(bool state);
void blink_tail_lights();
void turn_on_head_lights(bool state);
void blink_head_lights();
void honk_the_horn(bool state);

typedef enum{
	going_forward,
	going_reverse,
	destination_reached,
	stopped,
	num_of_indicator_states
}Indicator_states;

typedef struct{
	Indicator_states state;
}Indicator;

#endif /* L5_APPLICATION_SOURCE_INDICATORS_HPP_ */


#endif /* L5_APPLICATION_INDICATORS_H_ */
