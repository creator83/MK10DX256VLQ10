#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "pit.h"
#include "segled.h"

tact frq;

pit pit0 (pit::ch0, 1, pit::ms);
segled indicator (segled::E, segled::E);
//Gpio E (Gpio::E);

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;


extern "C" {
	void PIT0_IRQHandler();
}


void PIT0_IRQHandler()
{
	pit0.clear_flag ();
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
}


int main(void)
{
	indicator.get_buffer(4);
	/*E.setOutPort(0xFFF);
	E.setValPort(0xF00);
	E.setValPort(0x6D);*/

	while (1)
	{

	}
}
