#include "spi.h"

const uint32_t spi::Base_Adr [3] = {SPI0_BASE, SPI1_BASE, SPI2_BASE};

//CS,SCK,MISO,MOSI
uint8_t spi::pins_d[2][4]={{4,5,6,7},{6,3,4,5}};

PotMemFn spi::ptr_receive[2] = {&spi::receive_8, &spi::receive_16};

PotMemF spi::ptr_transmite[2] = {&spi::transmit_8, &spi::transmit_16};

Ptr_F spi::spi_init[3] = {&spi::spi0_init,&spi::spi1_init, &spi::spi2_init};

spi::spi(N_spi n_, PORT p, Division div, Cpol cpl, Cpha cph, Role r, Size s)
{
	SpiN_ = n_;
	port_ = p;
	size_ = s;
	(this->*(spi::spi_init[SpiN_]))();
}

void spi::spi0_init ()
{

}

void spi::spi1_init ()
{

}

void spi::spi2_init ()
{

}

void spi::Set_CS ()
{
  pin.setPin (pins_d[port_][CS]);
}

void spi::Clear_CS ()
{
  pin.clearPin (pins_d[port_][CS]);
}

void spi::transmit_8 (uint16_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);
}

void spi::transmit_16 (uint16_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	SPI1->DR = data;
}

void spi::transmit (uint16_t data)
{
	(this->*(spi::ptr_transmite[size_]))(data);
}

uint16_t spi::receive_8 ()
{
	//while (SPI1->SR&SPI_SR_BSY);
	//SPI1_DR_8bit  = 0xFF;
	//SPI1->DR = 0x0000;
	*(uint8_t *)&(SPI1->DR) = 0x00;
	while (!(SPI1->SR&SPI_SR_RXNE));
	//return  (SPI1_DR_8bit) ;	
	return static_cast <uint8_t>(SPI1->DR);	
}

uint16_t spi::receive_16 ()
{
	SPI1->DR = 0xFFFF;
	while (!(SPI1->SR&SPI_SR_RXNE));
	return SPI1->DR;	
}

uint16_t spi::receive ()
{
	 return (this->*(spi::ptr_receive[size_]))();
}

