#include "MK10D10.h"                    // Device header

#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms


void SysTick_Handler (void)
{
	
}


int main ()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR [1] = PORT_PCR_MUX(1);
	SysTick_Config (systick_val);
	
	while(1)
	{
	}
}
