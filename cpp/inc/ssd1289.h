#include "MK10D10.h"
#include "gpio.h"
#include "delay.h"
//#include "font.h"

//FMC pins
/*

PTC0 - D14
PTC1 - D13
PTC2 - D12
PTC3 - CLK
PTC4 - D11
PTC5 - D10
PTC6 - D9
PTC7 - D8
PTC8 - D7
PTC9 - D6
PTC10- D5
PTC11- RW
PTD1 - CS
PTD2 - D4
PTD3 - D3
PTD4 - D2
PTD5 - D1
PTD6 - D0
PTB17- DC
PTB18- D15
 */

#ifndef SSD1289_H
#define SSD1289_H

#define FMC_

const uint16_t BLACK =	0x0000;
const uint16_t BLUE	 =  0xF800;
const uint16_t RED 	 =  0x001F;
const uint16_t GREEN =	0x07E0;
const uint16_t CYAN	 =  0x07FF;
const uint16_t MAGENTA =0xF81F;
const uint16_t YELLOW =	0xFFE0;
const uint16_t WHITE =	0xFFFF;

const uint16_t GRAY	   =	 0xE79C;
const uint16_t SKY     =	 0x5d1C;
const uint16_t ORANGE  =   0xFCA0;
const uint16_t PINK    =	 0xF97F;
const uint16_t BROWN   =	 0x8200;
const uint16_t VIOLET  =	 0x9199;
const uint16_t SILVER  =   0xA510;
const uint16_t GOLD    =	 0xA508;
const uint16_t BEGH    =	 0xF77B;
const uint16_t NAVY    =	 0x000F;
const uint16_t DARK_GREEN =0x03E0;
const uint16_t DARK_CYAN  =0x03EF;
const uint16_t MAROON     =0x7800;
const uint16_t PURPLE     =0x7BE0;
const uint16_t LIGHT_GREY =0xC618;
const uint16_t DARK_GREY  =0x7BEF;

#define FLEX_DC_ADDRESS 0x60000000
#define FLEX_ADRESS_MASK 0x00010000
#define FLEX_BASE_ADDRESS FLEX_DC_ADDRESS+FLEX_ADRESS_MASK
// MUX mode + Wait States
#define FLEX_CSCR_MUX_MASK (FB_CSCR_BLS_MASK)
#define FLEX_CSMR_V_MASK FB_CSMR_V_MASK
#define FLEX_CSCR_AA_MASK FB_CSCR_AA_MASK
#define FLEX_CSCR_PS1_MASK (FB_CSCR_PS(2))


class ssd1289
{
//variables
public:
protected:
private:
#ifndef FMC_
	Gpio pinData;
	Gpio pinCommand;
	enum commPins {RST, CS, RS, WR ,RD};
#else
	Gpio B, C, D, pinCommand;
	enum commPins {RST,RD};
#endif

//functions
public:
	ssd1289();
	void point (uint16_t x , uint16_t y, uint16_t color);
	void fill_screen (uint16_t color);
	//void symbol (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, uint8_t ch);
	//void string (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, char *str);
	void set_cursor (uint16_t x , uint16_t y);
	void draw (uint16_t x , uint16_t y, uint16_t color, uint16_t phone, uint8_t *ch);
protected:
private:
	void init();
	void index(uint16_t indx);
	void data(uint16_t dta);
	void wr_reg (uint16_t indx , uint16_t dta);

}; //ssd1289

#endif //__SSD1289_H__
