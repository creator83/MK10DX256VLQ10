#include "MK10D10.h"
#include "gpio.h"


#define LED 6

Gpio A (Gpio::A);
extern "C" {
	void SysTick_Handler ();
	void PIT0_IRQHandler();
}

void SysTick_Handler ()
{
	PTA->PTOR |= 1 << LED;
}

void PIT0_IRQHandler()
{
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	//PTA->PTOR |= 1 << LED;
	A.ChangePinState(LED);
}

void pit_init (uint32_t div)
{
  SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
  PIT->MCR = 0;
  PIT->CHANNEL[0].LDVAL = div;
  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
  NVIC_EnableIRQ (PIT0_IRQn);
}

int main(void)
{
	A.setOutPin(LED);
	/*
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR [LED] |= PORT_PCR_MUX(1);
	PTA->PDDR |= 1 << LED;
	//PTA->PDOR |= 1 << LED;*/
	//SysTick_Config (SystemCoreClock/20);
	pit_init (0x2FAF080);
	while (1)
	{

	}
}
