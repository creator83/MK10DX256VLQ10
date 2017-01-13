#include "MK10D10.h"                // Device header
#include "gpio.h"

#ifndef PIN_H
#define PIN_H



class Pin: protected Gpio
{
//variables
public:

private:
	uint8_t pin_;
//functions
public:
	Pin (Port prt, uint8_t p , mux mx);
	Pin (Port prt, uint8_t p , out o);
	Pin (Port prt, uint8_t p , PP m);
	void direction (mode m);
	void setIn (PP pp_);
	void setOut (out o=out::PushPull);
	void set();
	void set (bool st);
	void clear ();
	void togle ();
	bool state ();
};

#endif



