#include "MK10D10.h"                // Device header
#include "gpio.h"

/*
 SPI0
 A: CS-14, SCK-15, MOSI-16, MISO-17
 C: CS-4, SCK-5, MOSI-6, MISO-7
 D: CS-0, SCK-1, MOSI-2, MISO-3
 E: CS-16, SCK-17, MOSI-18, MISO-19
 SPI1
 B: CS-10, SCK-11, MOSI-16, MISO-17
 E: CS-0, SCK-2, MOSI-1, MISO-3
 SPI2
 B: CS-20, SCK-21, MOSI-22, MISO-23
 D: CS-11, SCK-12, MOSI-13, MISO-14

 */



#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;

typedef void(spi::*PotMemF)(uint16_t) ;

typedef void(spi::*Ptr_F)() ;
class spi
{
//variables
public:

	enum N_spi {spi0,spi1,spi2};
	enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
	enum Role {slave , master};
	enum Cpol {neg, pos};
	enum Cpha {first, second};
	static uint8_t pins_d[2][4];
	enum Size {bit8, bit16};
	enum PORT {A,B,C,D,E};
	
	enum pin_def {CS, SCK , MISO , MOSI};
	uint8_t port_;
	uint8_t size_;
	uint8_t SpiN_;
private:
	//Gpio pin;
	static PotMemFn ptr_receive[2];
	static PotMemF ptr_transmite[2];
	static Ptr_F spi_init[3];

	static const uint32_t Base_Adr [3];
//functions
public:
	spi(N_spi n_, PORT p, Division div, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
	void spi0_init ();
	void spi1_init ();
	void spi2_init ();
	void set_CS ();
	void clear_CS ();
	void transmit_8 (uint16_t data);
	void transmit_16 (uint16_t data);
	void transmit (uint16_t data);
	uint16_t receive_8 ();
	uint16_t receive_16 ();
	uint16_t receive ();
private:
};

#endif

