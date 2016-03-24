#include "MK10D10.h"                   // Device header
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "pit.h"

tact frq;
const char led=17;





int main ()
{
	Gpio E (Gpio::E);
	E.setOutPin(led);

 
  while (1)
  {
	  E.ChangePinState(led);
	  delay_ms(1000);
  }
}
