#include "MK10D10.h"                    // Device header
#include "uart.h"
#include "tact.h"
#include "delay.h"

tact frq;

int main ()
{
	uart uart2 (uart::baud9600);

	while (1)
	{
		uart2.transmit ("Hello from Freescale!!!");
		delay_ms(2000);
		
	}
}
