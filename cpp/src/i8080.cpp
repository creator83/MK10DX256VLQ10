#include "i8080.h"

#define SOFT

#ifdef SOFT

i8080::i8080(MODE m)
:pinData (Gpio::C), pinCommand (Gpio::C)
{
	pinCommand.setOutPort(1 << RST|1 << WR|1 << CS|1 << RS|1 << RD);
	init();
}

void i8080::init_hardware ()
{

}


void i8080::index(uint16_t indx)
{
	//отправляем команду
	pinCommand.clearPin(RS);
	pinCommand.clearPin(CS);
	pinData.clearValPort (1 << RST|1 << WR|1 << CS|1 << RS|1 << RD);
	pinData.setValPort (indx >> 8);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	pinData.clearValPort (1 << RST|1 << WR|1 << CS|1 << RS|1 << RD);
	pinData.setValPort (static_cast <uint8_t>(indx));
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}

void i8080::data(uint16_t dta)
{

}
void ili9325::wr_reg (uint16_t indx , uint16_t dta)
{
	index(indx);
	data(dta);
}


/*void ili9325::wr_reg (uint16_t indx , uint16_t dta)
{
	index (indx);
	data (dta);
}
*/

void ili9325::set_cursor (uint16_t x , uint16_t y)
{
	wr_reg (0x20 , x);
	wr_reg(0x21 , y);
	index(0x0022);
}

void ili9325::point (uint16_t x , uint16_t y, uint16_t color)
{
	set_cursor(x,y);
	data(color);
}

void ili9325::fill_screen (uint16_t color)
{
	set_cursor(0,0);
	for (long i=0;i<76800;++i)
	{
		data(color);
	}
}

void ili9325::set_area (uint16_t x1 , uint16_t y1 , uint16_t x2 , uint16_t y2)
{
	x_start = x1;
	x_end = x2;
	y_start = y1;
	y_end = y2;
	wr_reg(h_Gram_start,x1);
	wr_reg(v_Gram_start,y1);
	wr_reg(h_Gram_end,x2);
	wr_reg(v_Gram_end,y2);
}

void ili9325::putchar (uint16_t x , uint16_t y , char * ch , uint16_t color , uint16_t background)
{
	set_cursor(x,y);
	
}

