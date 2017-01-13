#include "MK10D10.h"
#include "port.h"
#include "pin.h"

#ifndef I8080_H
#define I8080_H


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
PTB17- RS
PTB18- D15
 */
const uint32_t cPort = 0x7FF;
const uint32_t bPort = 0x60000;
const uint32_t dPort = 0x7E;

const uint32_t FLEXBUS_BASE_ADDRESS = 0x70000000;
const uint32_t LCD_COMMAND_ADDRESS = 0x70000000;
const uint32_t LCD_DATA_ADDRESS = 0x78000000;

//apnote

const uint32_t csMask = 0x10000;



class I8080
{
//variables
public:

protected:
private:
	Port b,c,d;
//functions
public:
	I8080();
	void index(uint16_t val);
	void data(uint16_t val);
	void wReg (uint16_t indx , uint16_t dta);

protected:
private:

};

#endif //__ILI9325_H__
