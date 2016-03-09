#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "pit.h"


tact frq;

pit pit0 (pit::ch0, 1000, pit::ms);

extern "C" {
	void PIT0_IRQHandler();
}


void PIT0_IRQHandler()
{
	pit0.clear_flag ();
}



int main(void)
{

	while (1)
	{

	}
}
