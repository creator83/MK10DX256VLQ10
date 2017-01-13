#include "i8080.h"

I8080::I8080()
:b(Gpio::Port::B, Gpio::mux::Alt5, bPort), c (Gpio::Port::C, Gpio::mux::Alt5, cPort),
 d(Gpio::Port::D, Gpio::mux::Alt5, dPort)
{
	SIM->SOPT2 |= SIM_SOPT2_FBSL(3);
	SIM->SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
	/*FB->CS[0].CSAR = FLEXBUS_BASE_ADDRESS;

	FB->CS[0].CSMR = FB_CSMR_BAM(0x0800)|FB_CSMR_V_MASK;
	FB->CS[0].CSCR = FB_CSCR_BLS_MASK|FB_CSCR_PS(2)| FB_CSCR_AA_MASK;

	FB->CSPMCR = FB_CSPMCR_GROUP3(2);*/
	FB->CS[0].CSMR = csMask|FB_CSMR_V_MASK;
	FB->CS[0].CSCR = FB_CSCR_BLS_MASK|FB_CSCR_AA_MASK|FB_CSCR_PS(2);
}

void I8080::index(uint16_t val)
{
	*(uint32_t*)LCD_COMMAND_ADDRESS = val;
}

void I8080::data(uint16_t val)
{
	*(uint32_t*)LCD_DATA_ADDRESS = val;
}

void I8080::wReg (uint16_t indx , uint16_t dta)
{
	index (indx);
	data (dta);
}
