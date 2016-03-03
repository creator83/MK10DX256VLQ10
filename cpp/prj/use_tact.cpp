#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"


tact frq;
#define LED 6
#define F_CPU 50000000
#define del_ms 1000
#define pit_val del_ms*(F_CPU/1000)



Gpio A (Gpio::A);
extern "C" {
	void PIT0_IRQHandler();
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
	//SysTick_Config (SystemCoreClock/20);
	//pit_init (pit_val);
	while (1)
	{
		A.ChangePinState(LED);
		delay_ms (1000);
	}
}
