#include "Indicators.h"
#include "gpio.hpp"

GPIO Tail_Light(P1_22);
GPIO Head_Light(P1_20);
GPIO Siren(P1_23);

Indicator t ;
void init_indicator_gpio()
{
	Tail_Light.setAsOutput();
	Tail_Light.setHigh();
	Head_Light.setAsOutput();
	Head_Light.setHigh();
	Siren.setAsOutput();
	Siren.setHigh();
}

void turn_on_tail_lights(bool state)
{
	Tail_Light.set(state);
}

void blink_tail_lights()
{
	Tail_Light.toggle();
}

void turn_on_head_lights(bool state)
{
	Head_Light.set(state);
}

void blink_head_lights()
{
	Head_Light.toggle();
}
void honk_the_horn(bool state)
{
	Siren.set(state);
}
