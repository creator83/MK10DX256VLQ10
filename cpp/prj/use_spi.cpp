#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"

tact frq;
const char CS=14;
const char SCK=15;
const char MOSI=16;
const char MISO=17;

//Tact port A
Gpio spi_pin (Gpio::A);

void spi0_transmit (uint8_t data);
void spi0_init ();

int main()
{
	spi0_init ();

  while (1)
  {

	  	spi_pin.clearPin(CS);
	  	spi0_transmit (0x0F);
		spi_pin.setPin(CS);
		delay_ms (1000);
		spi_pin.clearPin(CS);
		spi0_transmit (0xF0);
		spi_pin.setPin(CS);
		delay_ms (1000);
  }
}

void spi0_init ()
{

	//Setting pin CS as digital out
	spi_pin.setOutPin(CS);

	//
	spi_pin.setPin(CS);

	//Settings pins SCK, MOSI, MISO as ALT2
	spi_pin.setOutPort((1 << SCK|1 << MOSI|1 << MISO), Gpio::Alt2);

	//Turn on tacting SPI0
	SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;

	//Settings SPI0
	SPI0->MCR = SPI_MCR_HALT_MASK|SPI_MCR_MSTR_MASK | SPI_MCR_FRZ_MASK|SPI_MCR_ROOE_MASK|SPI_MCR_PCSIS(1)|SPI_MCR_DIS_TXF_MASK|SPI_MCR_DIS_RXF_MASK|SPI_MCR_CLR_TXF_MASK|SPI_MCR_CLR_RXF_MASK;

	SPI0->CTAR[1] = SPI_CTAR_PCSSCK(0)|SPI_CTAR_PASC(0)|SPI_CTAR_PBR(0)|SPI_CTAR_CSSCK(0)|SPI_CTAR_PDT(0)|SPI_CTAR_FMSZ(8-1);

	SPI0->CTAR[1] |= SPI_CTAR_BR(0x08);

	SPI0->CTAR[1] &= ~ (SPI_CTAR_CPHA_MASK|SPI_CTAR_CPOL_MASK|SPI_CTAR_LSBFE_MASK);

	SPI0->SR = SPI_SR_TCF_MASK|SPI_SR_EOQF_MASK|SPI_SR_TFUF_MASK|SPI_SR_TFFF_MASK|SPI_SR_RFOF_MASK|SPI_SR_RFOF_MASK;

	SPI0->MCR &= ~(SPI_MCR_HALT_MASK|SPI_MCR_FRZ_MASK);
}

void spi0_transmit (uint8_t data)
{
	while(!(SPI0->SR & SPI_SR_TCF_MASK));
	SPI0->PUSHR =SPI_PUSHR_CTAS(1)| SPI_PUSHR_TXDATA(data);
}

