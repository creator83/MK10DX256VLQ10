#include "tact.h"

uint8_t tact::f_cpu;

tact::tact ()
{
	
  f_cpu = 100;
 /* init_hsi ();
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMUL);
    
  RCC->CFGR |= RCC_CFGR_PLLMULL12;
  FLASH->ACR |= FLASH_ACR_PRFTBE;
  FLASH->ACR |= FLASH_ACR_LATENCY;
  
  RCC->CR |= RCC_CR_PLLON;
  
  while(!((RCC->CR)&RCC_CR_PLLRDY));
  RCC->CFGR &= RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!((RCC->CFGR)&RCC_CFGR_SWS_PLL ));*/
  
}

tact::tact (src_tact s)
{
  src = s;
  f_cpu = 48;
}

tact::tact (uint8_t frq, src_tact s )
{
}

void tact::init_FBE (uint8_t div)
{
	/*// If the internal load capacitors are being used, they should be selected
	// before enabling the oscillator. Application specific. 16 pF and 8 pF selected
	// in this example
	OSC_CR = OSC_CR_SC16P_MASK | OSC_CR_SC8P_MASK;*/
	// Enabling the oscillator for 8 MHz crystal
	// RANGE=1, should be set to match the frequency of the crystal being used
	// HGO=1, high gain is selected, provides better noise immunity but does draw
	// higher current
	// EREFS=1, enable the external oscillator
	// LP=0, low power mode not selected (not actually part of osc setup)
	// IRCS=0, slow internal ref clock selected (not actually part of osc setup)
	MCG->C2 = MCG_C2_EREFS0_MASK|MCG_C2_RANGE0(1)|MCG_C2_HGO0_MASK;
	/* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG->C1 = MCG_C1_FRDIV(3)|MCG_C1_CLKS(2);
	// wait for oscillator to initialize
	while (!(MCG->S & MCG_S_OSCINIT0_MASK));

	// wait for Reference clock to switch to external reference
	while (MCG->S & MCG_S_IREFST_MASK);

	// Wait for MCGOUT to switch over to the external reference clock
	while ((MCG->S&(1 << MCG_S_CLKST(2))) != 2);
	/* MCG->C4: DMX32=0,DRST_DRS=0 */
	MCG->C4 &= ~(MCG_C4_DRST_DRS(3)|MCG_C4_DMX32_MASK);
	// Now configure the PLL and move to PBE mode
	// set the PRDIV field to generate a 4 MHz reference clock (8
	// Now configure the PLL and move to PBE mode
	// set the PRDIV field to generate a 4 MHz reference clock (8 MHz /2)
	MCG->C5 = MCG_C5_PRDIV0(div);
}

void tact::init_hsi ()
{
	
}
void tact::Set_frq (uint8_t frq)
{
  if (frq>48) f_cpu = 48;
  else if (frq<4) f_cpu = 4;
  else f_cpu = (frq/4)*4;
  
}



