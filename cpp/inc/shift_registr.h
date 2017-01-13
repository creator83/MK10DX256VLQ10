#include "MK64F12.h"                 // Device header
#include "spi.h"
#include "pin.h"

namespace ShiftDef
{
//===Defenitions===//
//CS
const Gpio::Port CsPort = Gpio::Port::C;
const uint8_t CsPin = 0;
const Spi::CS_number CsNumber = Spi::CS_number::CS4;

//SCK
const Gpio::Port SckPort = Gpio::Port::E;
const uint8_t SckPin = 17;

//MOSI
const Gpio::Port MosiPort = Gpio::Port::E;
const uint8_t MosiPin = 18;

const Spi::CTAR_number CtarNumber = Spi::CTAR_number::CTAR1;
}

#ifndef SHIFT_REGISTR_H
#define SHIFT_REGISTR_H

class Shift
{
private:
	Gpio CS, SCK, MOSI;
	Spi * mod;

//functions
public:
	Shift (Spi &);
	void setMode ();
	void send (uint8_t data);
};
#endif
