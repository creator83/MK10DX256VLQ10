#include "MK10D10.h"
#include "gpio.h"

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



class i8080
{
//variables
public:
	enum MODE {Hardware, Software_16, Software_8};
protected:
private:

	Gpio pinData;
	Gpio pinCommand;
	enum commPins_soft {RST=3, CS=4, RS=2, WR=1 ,RD=0};
	enum commPins_soft {RST=3, CS=4, RS=2, WR=1 ,RD=0};
	enum commPins_soft {RST=3, CS=4, RS=2, WR=1 ,RD=0};
	enum commPins_hard {RST = 14,RD};
	Gpio B, C, D;


//functions
public:
	i8080(MODE m);

protected:
private:
	void init_hardware ();
	void init_software16 ();
	void init_software8 ()
	void index(uint16_t indx);
	void data(uint16_t dta);
	void wr_reg (uint16_t indx , uint16_t dta);
	void wr_reg_hardware (uint16_t indx , uint16_t dta);
	void wr_reg_software8 (uint16_t indx , uint16_t dta);
	void wr_reg_software16 (uint16_t indx , uint16_t dta);
	void data_raw (uint16_t dta);
	void data_latch ();
	inline void data_prepare (){pinCommand.clearPin(CS);pinCommand.setPin(RS)};


};

#endif //__ILI9325_H__
