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
  if (s) init_hse();
  else init_hsi();
  
  init_pll();
}

tact::tact (uint8_t frq, src_tact s )
{
  Set_frq(frq);
  src = s;
  
  if (s) init_hse();
  else init_hsi();

  init_pll(f_cpu);
}

void tact::init_hse ()
{
	/* SIM->CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	SIM_CLKDIV1 = 0x00110000u; /* Update system prescalers */
	/* Switch to FBE Mode */
	/* OSC->CR: ERCLKEN=0,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC_CR = 0x00u;
	/* MCG->C7: OSCSEL=0 */
	MCG_C7 = 0x00u;
	/* MCG->C2: ??=0,??=0,RANGE0=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
	MCG_C2 = 0x24u;
	/* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = 0x9Au;
	/* MCG->C4: DMX32=0,DRST_DRS=0 */
	MCG_C4 &= (uint8_t)~(uint8_t)0xE0u;
	/* MCG->C5: ??=0,PLLCLKEN=0,PLLSTEN=0,PRDIV0=3 */
	MCG_C5 = 0x03u;
	/* MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0 */
	MCG_C6 = 0x00u;	 
	while((MCG_S & MCG_S_OSCINIT0_MASK) == 0u); /* Check that the oscillator is running */
	
	while((MCG_S & MCG_S_IREFST_MASK) != 0u) ; /* Check that the source of the FLL reference clock is the external reference clock. */
	
	while((MCG_S & 0x0Cu) != 0x08u) ;    /* Wait until external reference clock is selected as MCG output */
	
	/* Switch to PBE Mode */
	/* MCG_C5: ??=0,PLLCLKEN=0,PLLSTEN=0,PRDIV0=1 */
	MCG_C5 = 0x01u;
	  /* MCG->C6: LOLIE=0,PLLS=1,CME=0,VDIV0=1 */
	  MCG_C6 = 0x41u;
	  while((MCG_S & MCG_S_PLLST_MASK) == 0u) ; /* Wait until the source of the PLLS clock has switched to the PLL */
	  
	  while((MCG_S & MCG_S_LOCK0_MASK) == 0u) ; /* Wait until locked */
	  
	  
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

//Init PLL
void tact::init_pll ()
{
	/* Switch to PEE Mode */
	/* MCG->C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = (uint8_t)0x1Au;
	while((MCG_S & 0x0Cu) != 0x0Cu) ;    /* Wait until output of the PLL is selected */
	
	while((MCG_S & MCG_S_LOCK0_MASK) == 0u) ; /* Wait until locked */
	
}    

void tact::init_pll (uint8_t i)
{

}

