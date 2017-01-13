#include "gpio.h"

GPIO_MemMapPtr Gpio::GpioBase [5] = {PTA_BASE_PTR , PTB_BASE_PTR , PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR};
PORT_MemMapPtr Gpio::PortBase [5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};


Gpio::Gpio ()
{

}

Gpio::Gpio (Port p)
{
  prt = static_cast <uint8_t> (p);
  //takt port
  SIM->SCGC5 |= (0x200 << prt);
}

void Gpio::setPort (Port p)
{
	prt = static_cast <uint8_t> (p);
	//takt port
	SIM->SCGC5 |= (0x200 << prt);
}


void Gpio::setValPort (uint32_t value)
{
	GPIO_PSOR_REG(GpioBase[prt])  |= value;
}

void Gpio::clearValPort (uint32_t value)
{
	GPIO_PCOR_REG(GpioBase[prt])  |= value;
}

