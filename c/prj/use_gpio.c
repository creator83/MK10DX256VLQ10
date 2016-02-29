<<<<<<< HEAD
#include <MK10D10.h>           

#define LED 6
=======
#include "MK10D10.h"                    // Device header

#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms


void SysTick_Handler (void)
{
	
}

>>>>>>> efc09151a69a32afffe4279808f9ef47a5984423

int main ()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
<<<<<<< HEAD
	PORTA->PCR [LED] |= PORT_PCR_MUX(1);
	PTA->PDDR |= 1 << LED;
	PTA->PDOR |= 1 << LED;
	while (1)
	{
		
=======
	PORTA->PCR [1] = PORT_PCR_MUX(1);
	SysTick_Config (systick_val);
	
	while(1)
	{
>>>>>>> efc09151a69a32afffe4279808f9ef47a5984423
	}
}
