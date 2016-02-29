#include "MK10D10.h"                   // Device header
#include "gpio.h"
#include "tact.h"

const char led=6;

int main ()
{
	SysTick_Config (SystemCoreClock/1000000);
	Gpio A (Gpio::A);
	A.setOutPort(0xF0);
	A.setValPort(0xF0);
	A.clearValPort(0xF0);
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT_MCR |= 0X00;
	//enable_irq (INT_PIT0-16);
 
  while (1)
  {

  }
}
