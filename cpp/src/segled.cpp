#include "segled.h"

char segled::number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
char segled::pins[4] = {first, second, third, fourth};

segled::segled (Port seg, Port dig)
:pin_segment (seg), pin_digit (dig)
{
	//===Settings segment pins===//
	pin_segment.setOutPort((1<<a|1<<b|1<<c|1<<d|1<<e|1<<f|1<<g|1<<dp), Gpio::Alt1);


	//===Settings digit pins===//
	pin_digit.setOutPort((1<<first|1<<second|1<<third|1<<fourth), Gpio::Alt1);
	
}

void segled::OFF ()
{
	pin_digit.clearValPort(1<<first|1<<second|1<<third|1<<fourth);
}

void segled::frame (uint8_t dig)
{
	pin_digit.clearValPort(1<<first|1<<second|1<<third|1<<fourth);
	pin_segment.clearValPort(1<<a|1<<b|1<<c|1<<d|1<<e|1<<f|1<<g|1<<dp);
	pin_digit.setPin (pins[dig]);
	pin_segment.setValPort (number[buffer[dig]]);
}

void segled::digit ()
{
	static uint8_t i=0;
	frame (i);
	++i;
	if (i>=n)i=0;
}

void segled::get_buffer (uint16_t val)
{
	char tous, hundr, dec, ones;
	uint16_t temp = val;

	for (tous=0;temp>=1000;++tous)temp -=1000;

	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;

	if (tous)
	{	
		buffer[3] = tous;
		buffer[2] = hundr;
		buffer[1] = dec;
		buffer[0] = ones;
		n=4;
	}
	else if (!(tous || hundr))
	{
		buffer[1] = dec;
		buffer[0] = ones;
		n=2;
	}
	else if (!(tous || hundr||dec))
	{
		buffer[0] = ones;
		n=1;
	}	
	else
	{
		buffer[2] = hundr;
		buffer[1] = dec;
		buffer[0] = ones;
		n=3;
	}
}
