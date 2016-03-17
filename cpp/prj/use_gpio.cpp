#include "MK10D10.h"                   // Device header
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "pit.h"

tact frq;
const char led=18;





int main ()
{
	Gpio B (Gpio::B);
	B.setOutPin(led);

 
  while (1)
  {
	  B.ChangePinState(led);
	  delay_ms(1000);
  }
}
