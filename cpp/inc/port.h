#include "MK10D10.h"                // Device header
#include "gpio.h"

#ifndef PORT_H
#define PORT_H



class Port: protected Gpio
{
//functions
public:
	Port (Gpio::Port prt, uint32_t value);
	Port (Gpio::Port prt, mux mx, uint32_t value);
	void set(uint32_t value);
	void set (uint32_t value, bool st);
	void clear (uint32_t value);
	void togle (uint32_t value);
};

#endif



