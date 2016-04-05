#include "MK10D10.h"                // Device header
#include "gpio.h"

/*
 SPI0
 A: CS0-14, SCK-15, MOSI-16, MISO-17
 C: CS4-0, CS3-1, CS2-2, CS1-3, CS0-4, SCK-5, MOSI-6, MISO-7
 D: CS0-0, CS1-4, CS2-5, CS3-6,SCK-1, MOSI-2, MISO-3
 E: CS0-16, SCK-17, MOSI-18, MISO-19
 SPI1
 B: CS0-10, CS1-9, SCK-11, MOSI-16, MISO-17
 E: CS1-0, SCK-2, MOSI-1, MISO-3
 SPI2
 B: CS0-20, SCK-21, MOSI-22, MISO-23
 D: CS0-11, CS1-15, SCK-12, MOSI-13, MISO-14

 */

const uint8_t SPI0_CS0 = 2;

#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;

typedef void(spi::*PotMemF)(uint16_t) ;

typedef void(spi::*Ptr_F)() ;

typedef uint8_t (*Ptr)[2][5] ;

typedef unsigned int* reg;

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
	enum Size {bit8 = 8, bit16 = 16};
	enum PORT {A,B,C,D,E};
	
	enum pin_def {SCK ,  MOSI, MISO};
	enum pin_CS {CS0, CS1, CS2, CS3, CS4};
	uint8_t port_;
	uint8_t size_;
	uint8_t SpiN_;
	uint8_t role_;
	uint8_t pin_cs_;
private:
	Gpio pin;
	static PotMemFn ptr_receive[2];
	static PotMemF ptr_transmite[2];
	static Ptr_F spi_init[3];
	static uint8_t spi0_A_pins [2][5];
	static uint8_t spi0_C_pins [2][5];
	static uint8_t spi0_D_pins [2][5];
	static uint8_t spi0_E_pins [2][5];
	static const uint8_t spi1_B_pins [2][5];
	static const uint8_t spi1_E_pins [2][5];
	static const uint8_t spi2_B_pins [2][5];
	static const uint8_t spi2_D_pins [2][5];
	static Ptr ptr_spi[5];
	//static ptr_pins pins_ptr_spi1 [2];
	//static ptr_pins pins_ptr_spi2 [2];
	//static uint8_t spi2_D_pins [2][5];


	static const uint32_t Base_Adr [3];
//functions
public:
	spi(N_spi n_, PORT p, Division div, pin_CS cs_, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
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

