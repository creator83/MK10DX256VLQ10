
#include <MK10D10.h>           

#define LED 7
 

void SysTick_Handler (void)
{
	//PTA->PTOR |= 1 << LED;
}

int main ()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTA->PCR [LED] |= PORT_PCR_MUX(1);
	PTA->PDDR |= 1 << LED;
	PTA->PDOR |= 1 << LED;
	SysTick_Config (SystemCoreClock/1000);
	
	while(1)
	{

	}
}
