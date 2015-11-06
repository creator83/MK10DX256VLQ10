#include "MK10D10.h"                    // Device header

int main ()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR [1] = PORT_PCR_MUX(1);
	
	while(1)
	{
	}
}
