#include "ssd1289.h"


ssd1289::ssd1289()
:pinData (Gpio::D) , pinCommand (Gpio::E)
{
	//Settings pins Bus
	pinData.setOutPort(0xFFFF);
	//Settings pin command
	pinCommand.setOutPort (1<<CS|1<<RS|1<<RST|1<<RD|1<<WR);
	pinCommand.setPin(CS);
	pinCommand.setPin(RD);
	pinCommand.setPin(WR);
	pinCommand.clearPin(RST);
	delay_ms(100);
	pinCommand.setPin(RST);
	init();
} //ssd1289

void ssd1289::index(uint16_t indx)
{
	pinCommand.clearPin(CS);
	//отправляем команду
	pinCommand.clearPin(RS);
	pinData.setValPort(indx);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}

void ssd1289::data(uint16_t dta)
{
	pinCommand.clearPin(CS);
	//отправляем данные
	pinCommand.setPin(RS);
	pinData.setValPort(dta);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}

void ssd1289::wr_reg (uint16_t indx , uint16_t dta)
{
	pinCommand.clearPin(CS);
	//отправляем команду
	pinCommand.clearPin(RS);
	pinData.setValPort(indx);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	//отправляем данные
	pinCommand.setPin(RS);
	pinData.setValPort(dta);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);

}

/*

ssd1289::ssd1289()
:B(Gpio::B), C(Gpio::C), D(Gpio::D), pinCommand (Gpio::C)
{
	B.setOutPort ((1<<17|1<<18),Gpio::Alt5);
	C.setOutPort (0xFFF, Gpio::Alt5);
	D.setOutPort ((1<<1|1<<2|1<<3|1<<4|1<<5|1<<6),Gpio::Alt5);
	pinCommand.setOutPin(RST);
	pinCommand.setOutPin(RD);
	pinCommand.setPin(RST);
	pinCommand.setPin(RD);
	SIM->SOPT2 |= SIM_SOPT2_FBSL(3);
	SIM->SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
	// CS0 base address
	FB->CS[0].CSAR = FLEX_DC_ADDRESS;

	// The address range is set to 128K	because the DC signal is connected on address wire
	FB->CS[0].CSMR = FB_CSMR_V_MASK|FLEX_ADRESS_MASK;

	FB->CS[0].CSCR = FLEX_CSCR_MUX_MASK | FLEX_CSCR_AA_MASK | FLEX_CSCR_PS1_MASK;
}

void ssd1289::index(uint16_t value)
{

	*((unsigned short*)FLEX_DC_ADDRESS) = value;
}

void ssd1289::data(uint16_t dta)
{
	*((unsigned short*)FLEX_BASE_ADDRESS) = dta;
}

void ssd1289::wr_reg (uint16_t indx , uint16_t dta)
{
	index (indx);
	data (dta);
}
*/

void ssd1289::point (uint16_t x , uint16_t y, uint16_t color)
{
	set_cursor(x,y);
	index(0x0022);
	data (color);	
}

void ssd1289::fill_screen_l (uint16_t color)
{
	set_cursor(0,0);
	index(0x0022);
	for (long i=0;i<76800;++i)data(color);
}


void ssd1289::fill_screen (uint16_t color)
{
	set_cursor(0,0);
	index(0x0022);
	pinCommand.clearPin(CS);
	//отправляем данные
	pinCommand.setPin(RS);
	pinData.setValPort(color);
	for (long i=0;i<76800;++i)
		{
			pinCommand.clearPin(WR);
			pinCommand.setPin(WR);
		}
}

void ssd1289::data_raw (uint16_t dta)
{
	pinData.setValPort(dta);
	pinCommand.clearPin(WR);
	pinCommand.setPin(WR);
}

void ssd1289::set_cursor (uint16_t x , uint16_t y)
{
	wr_reg(0x004e, x);
	wr_reg(0x004f, y);
}

void ssd1289::symbol (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, uint8_t ch)
{
	uint8_t pos = ch -32;
	for(int8_t j=0; j<8; j++)          
  { 
		set_cursor(x+j,y);
		for(int8_t i=0; i<8; i++)          //??? 8-?? ???????? ?? y
    {
			if(0x01&(big[pos][j]>>(7-i)))   //???? 1 - ????? ????? ????? ???????
      {
				data(color);
      }
      else    //???? 0 - ????? ????? ????? ????
      {
				data(phone);
      }
	}
  }
}

void ssd1289::string (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, char *str)
{
	while (*str)
	{
		symbol (x,y,color,phone,*str);
		str++;
		y-=8;
	}
}

void  ssd1289::draw (uint16_t x , uint16_t y, uint16_t color, uint16_t phone, uint8_t *ch)
{
	
	for(uint8_t j=0; j<8; j++, ch++)          
  {
		set_cursor(x+j,y);
		for(uint8_t i=0; i<8; i++)          //??? 8-?? ???????? ?? y
    {
			if(0x01&(*ch>>(7-i)))   //???? 1 - ????? ????? ????? ???????
      {
				data(color);
      }
      else    //???? 0 - ????? ????? ????? ????
      {
				data(phone);
      }
			//delay_ms(500);
		}
  }
}



void ssd1289::init()
{

	/*	wr_reg(0X0007, 0X0021);   //далее записываем в регистры значения
	wr_reg(0X0000, 0X0001);
	wr_reg(0X0007, 0X0023);
	wr_reg(0X0010, 0X0000);
	delay_ms(30);
	wr_reg(0X0007, 0X0033);
	wr_reg(0X0011, 0X6838);
	wr_reg(0X0002, 0X0600);	

	wr_reg(0x00,0x0001);
	wr_reg(0x03,0xA8A4);
	wr_reg(0x0C,0x0000);
	wr_reg(0x0D,0x080C);
	wr_reg(0x0E,0x2B00);
	wr_reg(0x1E,0x00B7);
	wr_reg(0x01,0x2B3F);
	wr_reg(0x02,0x0600);
	wr_reg(0x10,0x0000);
	wr_reg(0x11,0x6058);
	wr_reg(0x05,0x0000);
	wr_reg(0x06,0x0000);
	wr_reg(0x16,0xEF1C);
	wr_reg(0x17,0x0003);
	wr_reg(0x07,0x0233);
	wr_reg(0x0B,0x0000);
	wr_reg(0x0F,0x0000);
	wr_reg(0x41,0x0000);
	wr_reg(0x42,0x0000);
	wr_reg(0x48,0x0000);
	wr_reg(0x49,0x013F);
	wr_reg(0x4A,0x0000);
	wr_reg(0x4B,0x0000);
	wr_reg(0x44,0xEF00);
	wr_reg(0x45,0x0000);
	wr_reg(0x46,0x013F);
	wr_reg(0x30,0x0707);
	wr_reg(0x31,0x0204);
	wr_reg(0x32,0x0204);
	wr_reg(0x33,0x0502);
	wr_reg(0x34,0x0507);
	wr_reg(0x35,0x0204);
	wr_reg(0x36,0x0204);
	wr_reg(0x37,0x0502);
	wr_reg(0x3A,0x0302);
	wr_reg(0x3B,0x0302);
	wr_reg(0x23,0x0000);
	wr_reg(0x24,0x0000);
	wr_reg(0x25,0x8000);
	wr_reg(0x4f,0x0000);
	wr_reg(0x4e,0x0000);
	index(0x22);  */
	
	
	
	
	wr_reg(0x00,0x0001);
	wr_reg(0x03,0xA8A4);
	wr_reg(0x0C,0x0000);
	wr_reg(0x0D,0x080C);
	wr_reg(0x0E,0x2B00);
	wr_reg(0x1E,0x00B7);
	wr_reg(0x01,0x2B3F);
	wr_reg(0x02,0x0600);
	wr_reg(0x10,0x0000);
	delay_ms(30);
	wr_reg(0x11,0x6058);//direction
	wr_reg(0x05,0x0000);
	wr_reg(0x06,0x0000);
	wr_reg(0x16,0xEF1C);
	wr_reg(0x17,0x0003);
	wr_reg(0x07,0x0233);
	wr_reg(0x0B,0x0000);
	wr_reg(0x0F,0x0000);
	wr_reg(0x41,0x0000);
	wr_reg(0x42,0x0000);
	wr_reg(0x48,0x0000);
	wr_reg(0x49,0x013F);
	wr_reg(0x4A,0x0000);
	wr_reg(0x4B,0x0000);
	wr_reg(0x44,0xEF00);
	wr_reg(0x45,0x0000);
	wr_reg(0x46,0x013F);
	wr_reg(0x30,0x0707);
	wr_reg(0x31,0x0204);
	wr_reg(0x32,0x0204);
	wr_reg(0x33,0x0502);
	wr_reg(0x34,0x0507);
	wr_reg(0x35,0x0204);
	wr_reg(0x36,0x0204);
	wr_reg(0x37,0x0502);
	wr_reg(0x3A,0x0302);
	wr_reg(0x3B,0x0302);
	wr_reg(0x23,0x0000);
	wr_reg(0x24,0x0000);
	wr_reg(0x25,0x8000);
	wr_reg(0x4f,0x0000);
	wr_reg(0x4e,0x0000);
	index(0x22);
}



