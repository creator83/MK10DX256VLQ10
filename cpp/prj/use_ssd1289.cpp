#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "pit.h"
#include "segled.h"
#include "ssd1289.h"

tact frq;

uint16_t mass [24] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE, GRAY, SKY, ORANGE, PINK, BROWN, VIOLET, SILVER, GOLD, BEGH, NAVY, DARK_GREEN, DARK_CYAN, MAROON, PURPLE, LIGHT_GREY, DARK_GREY};
uint8_t font [8] = {0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00};
	
int main()
{
	ssd1289 lcd;
	lcd.fill_screen(BLACK);
	lcd.draw (50,50,WHITE,BLACK, font);
	lcd.string(50,50,RED,GREEN, "Hello from Freescale");
	delay_ms (2000);
  while (1)
  {

		
		
		for (uint8_t i=0;i<24;++i)
		{
			lcd.fill_screen(mass [i]);
			delay_ms (1000);
		}
  }
}
