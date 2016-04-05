#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "spi.h"

tact frq;
const char CS=9;
const char SCK=11;
const char MOSI=16;
const char MISO=17;

//Tact port A
Gpio spi_pin (Gpio::B);

void spi1_transmit (uint8_t data);
void spi1_init ();

int main()
{
	spi1_init ();

  while (1)
  {
	  for (int8_t i=0;i<8;++i)
	  {
		  spi1_transmit (1<<i);
		  delay_ms(200);
	  }
	  for (int8_t i=6;i>0;--i)
	  {
		  spi1_transmit (1<<i);
		  delay_ms(100);
	  }
  }
}

void spi1_init ()
{

	//Setting pin CS as digital out
	//spi_pin.setOutPin(CS);

	//
	//spi_pin.setPin(CS);

	//Settings pins SCK, MOSI, MISO as ALT2
	spi_pin.setOutPort((1 << CS|1 << SCK|1 << MOSI|1 << MISO), Gpio::Alt2);

	//Turn on tacting SPI0
	SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;

	//Settings SPI1

	SPI1->MCR = SPI_MCR_DCONF (0);
	SPI1->MCR |= SPI_MCR_MSTR_MASK | SPI_MCR_PCSIS(1 << 1) |SPI_MCR_DIS_TXF_MASK|SPI_MCR_DIS_RXF_MASK;



	//SPI1_MCR = SPI_MCR_MSTR_MASK | SPI_MCR_ROOE_MASK | SPI_MCR_PCSIS(2) | SPI_MCR_DIS_TXF_MASK | SPI_MCR_DIS_RXF_MASK | SPI_MCR_CLR_TXF_MASK | SPI_MCR_CLR_RXF_MASK | SPI_MCR_HALT_MASK; //Set Configuration register

	SPI1->CTAR[0] = SPI_CTAR_FMSZ(7) | SPI_CTAR_PASC(1) |  SPI_CTAR_PBR(1)| SPI_CTAR_BR(0x0E)
	//|SPI_CTAR_PCSSCK(2)|SPI_CTAR_CSSCK(2)
	;

	//SPI0->CTAR[1] &= ~ (SPI_CTAR_CPHA_MASK|SPI_CTAR_CPOL_MASK|SPI_CTAR_LSBFE_MASK);
	//SPI1->CTAR[0] = SPI_CTAR_FMSZ(7) | SPI_CTAR_BR(0x0E);

	SPI1->SR = SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK | SPI_SR_TXCTR(0) | SPI_SR_TXNXTPTR(0) | SPI_SR_RXCTR(0) | SPI_SR_POPNXTPTR(0); //Clear flags
	SPI1->MCR &= ~SPI_MCR_HALT_MASK;
}

void spi1_transmit (uint8_t data)
{
	while(!(SPI1->SR &SPI_SR_TFFF_MASK));
	SPI1->PUSHR =SPI_PUSHR_PCS(1 << 1)| SPI_PUSHR_CTAS(0)|SPI_PUSHR_TXDATA(data);
	while(!(SPI1->SR &SPI_SR_TCF_MASK));
}

