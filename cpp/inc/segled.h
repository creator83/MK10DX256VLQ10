#include "MK10D10.h"                // Device header
#include "gpio.h"
#include "pit.h"

#ifndef SEGLED_H
#define SEGLED_H

class segled
{
//variables
public:	
	enum Port {A , B , C , D, E};
	enum Segment {a, b, c, d, e, f, g, dp};
	//enum Segment {a, b, c, d, e, f, g};
	enum Digit {first=8, second, third, fourth};
	char buffer [4];
private:
	Gpio pin_segment;
	Gpio pin_digit;
	static char number [13];
	static char pins [4];
	char n;
//functions

public:	
	segled (Port seg, Port dig);
	void OFF ();
	void get_buffer (uint16_t val);
	void digit ();
	void frame (uint8_t dig);
private:
	
	
};


#endif
