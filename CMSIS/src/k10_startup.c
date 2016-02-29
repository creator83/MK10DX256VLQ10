/**
 *****************************************************************************
 **
 **  File        : k10_startup.c
 **
 **  Abstract    : This file contains interrupt vector and startup code.
 **
 **  Functions   : Reset_Handler() and Default_Handler()
 **
 **  Target     : Freescale Kinetis K10 microcontrollers
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **
 **  Distribution: The file is distributed "as is", without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. This file may only be built (assembled or compiled and linked)
 **  using the Atollic TrueSTUDIO(R) product. The use of this file together
 **  with other tools than Atollic TrueSTUDIO(R) is not permitted.
 **
 *****************************************************************************
 */

/**
 **===========================================================================
 **  Revisions
 **===========================================================================
 **       Date        Modification
 **       2011-09-07  First issue.
 **===========================================================================
 */

#include "MK10DZ10.h"

/**
 **===========================================================================
 **  External declarations
 **===========================================================================
 */
extern unsigned long _sdata, _edata, _sidata, _sbss, _ebss;
extern unsigned long _estack;
extern void __libc_init_array();
extern void SystemInit();
extern void main();

#define DISABLE_WDOG 1

/**
 **===========================================================================
 **  Default interrupt handler
 **===========================================================================
 */
void Default_Handler() {
  /* Hang here */
  while (1) {
  }
}

/**
 **===========================================================================
 **  Reset handler
 **===========================================================================
 */
__attribute__((naked)) void Reset_Handler() {
  /* Data and BSS variables */
  unsigned long *srcdata, *dstdata, *sbss;

  /* Set up the stack pointer */
  asm("ldr sp,=_estack\n\t");

  srcdata = &_sidata;
  dstdata = &_sdata;
  sbss = &_sbss;

#if (DISABLE_WDOG)
  /* Disable the WDOG module */
  /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = (uint16_t)0xC520u; /* Key 1 */
  /* WDOG_UNLOCK : WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK = (uint16_t)0xD928u; /* Key 2 */
  /* WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,STNDBYEN=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = (uint16_t)0x01D2u;
#endif /* (DISABLE_WDOG) */

  /* Copy data */
  while (dstdata != &_edata) {
    *(dstdata++) = *(srcdata++);
  }

  /* Clear BSS */
  while (sbss != &_ebss) {
    *(sbss++) = '\0';
  }

  /* Run static constructors */
  __libc_init_array();

  /* Initialize System */
  SystemInit();

  /* Jump to main */
  main();

  /* In case main returns, use default handler */
  Default_Handler();
}

/* Weak definitions of handlers point to Default_Handler if not implemented */
void NMI_Handler() __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler() __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DebugMonitor_Handler() __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler() __attribute__ ((weak, alias("Default_Handler")));

void DMA0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA3_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA4_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA5_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA6_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA7_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA8_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA9_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA10_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA11_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA12_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA13_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA14_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA15_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA_Error_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MCM_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTFL_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void Read_Collision_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LVD_LVW_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LLW_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void Watchdog_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RNG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_ORed_Message_buffer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Bus_Off_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Error_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Tx_Warning_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Rx_Warning_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Wake_Up_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_ORed_Message_buffer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Bus_Off_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Error_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Tx_Warning_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Rx_Warning_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Wake_Up_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART0_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART0_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART1_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART1_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART2_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART2_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART3_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART3_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART4_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART4_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART5_RX_TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART5_ERR_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMP0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMP1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMP2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMT_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT3_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PDB0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void USB0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void USBDCD_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ENET_1588_Timer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ENET_Transmit_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ENET_Receive_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ENET_Error_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2S0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SDHC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DAC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DAC1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TSI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MCG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LPTimer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTA_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTB_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTD_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTE_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));

/* The Interrupt Vector Table */
void (* const InterruptVector[])() __attribute__ ((section(".isr_vector"))) = {
    /* Processor exceptions */
    (void(*)(void)) &_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMonitor_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* Interrupts */
    DMA0_IRQHandler, /* DMA Channel 0 Transfer Complete */
    DMA1_IRQHandler, /* DMA Channel 1 Transfer Complete */
    DMA2_IRQHandler, /* DMA Channel 2 Transfer Complete */
    DMA3_IRQHandler, /* DMA Channel 3 Transfer Complete */
    DMA4_IRQHandler, /* DMA Channel 4 Transfer Complete */
    DMA5_IRQHandler, /* DMA Channel 5 Transfer Complete */
    DMA6_IRQHandler, /* DMA Channel 6 Transfer Complete */
    DMA7_IRQHandler, /* DMA Channel 7 Transfer Complete */
    DMA8_IRQHandler, /* DMA Channel 8 Transfer Complete */
    DMA9_IRQHandler, /* DMA Channel 9 Transfer Complete */
    DMA10_IRQHandler, /* DMA Channel 10 Transfer Complete */
    DMA11_IRQHandler, /* DMA Channel 11 Transfer Complete */
    DMA12_IRQHandler, /* DMA Channel 12 Transfer Complete */
    DMA13_IRQHandler, /* DMA Channel 13 Transfer Complete */
    DMA14_IRQHandler, /* DMA Channel 14 Transfer Complete */
    DMA15_IRQHandler, /* DMA Channel 15 Transfer Complete */
    DMA_Error_IRQHandler, /* DMA Error Interrupt */
    MCM_IRQHandler, /* Normal Interrupt */
    FTFL_IRQHandler, /* FTFL Interrupt */
    Read_Collision_IRQHandler, /* Read Collision Interrupt */
    LVD_LVW_IRQHandler, /* Low Voltage Detect, Low Voltage Warning */
    LLW_IRQHandler, /* Low Leakage Wake-up */
    Watchdog_IRQHandler, /* WDOG Interrupt */
    RNG_IRQHandler, /* RNGB Interrupt */
    I2C0_IRQHandler, /* I2C0 interrupt */
    I2C1_IRQHandler, /* I2C1 interrupt */
    SPI0_IRQHandler, /* SPI0 Interrupt */
    SPI1_IRQHandler, /* SPI1 Interrupt */
    SPI2_IRQHandler, /* SPI2 Interrupt */
    CAN0_ORed_Message_buffer_IRQHandler, /* CAN0 OR'd Message Buffers Interrupt */
    CAN0_Bus_Off_IRQHandler, /* CAN0 Bus Off Interrupt */
    CAN0_Error_IRQHandler, /* CAN0 Error Interrupt */
    CAN0_Tx_Warning_IRQHandler, /* CAN0 Tx Warning Interrupt */
    CAN0_Rx_Warning_IRQHandler, /* CAN0 Rx Warning Interrupt */
    CAN0_Wake_Up_IRQHandler, /* CAN0 Wake Up Interrupt */
    Default_Handler, /* Reserved interrupt 51 */
    Default_Handler, /* Reserved interrupt 52 */
    CAN1_ORed_Message_buffer_IRQHandler, /* CAN1 OR'd Message Buffers Interrupt */
    CAN1_Bus_Off_IRQHandler, /* CAN1 Bus Off Interrupt */
    CAN1_Error_IRQHandler, /* CAN1 Error Interrupt */
    CAN1_Tx_Warning_IRQHandler, /* CAN1 Tx Warning Interrupt */
    CAN1_Rx_Warning_IRQHandler, /* CAN1 Rx Warning Interrupt */
    CAN1_Wake_Up_IRQHandler, /* CAN1 Wake Up Interrupt */
    Default_Handler, /* Reserved interrupt 59 */
    Default_Handler, /* Reserved interrupt 60 */
    UART0_RX_TX_IRQHandler, /* UART0 Receive/Transmit interrupt */
    UART0_ERR_IRQHandler, /* UART0 Error interrupt */
    UART1_RX_TX_IRQHandler, /* UART1 Receive/Transmit interrupt */
    UART1_ERR_IRQHandler, /* UART1 Error interrupt */
    UART2_RX_TX_IRQHandler, /* UART2 Receive/Transmit interrupt */
    UART2_ERR_IRQHandler, /* UART2 Error interrupt */
    UART3_RX_TX_IRQHandler, /* UART3 Receive/Transmit interrupt */
    UART3_ERR_IRQHandler, /* UART3 Error interrupt */
    UART4_RX_TX_IRQHandler, /* UART4 Receive/Transmit interrupt */
    UART4_ERR_IRQHandler, /* UART4 Error interrupt */
    UART5_RX_TX_IRQHandler, /* UART5 Receive/Transmit interrupt */
    UART5_ERR_IRQHandler, /* UART5 Error interrupt */
    ADC0_IRQHandler, /* ADC0 interrupt */
    ADC1_IRQHandler, /* ADC1 interrupt */
    CMP0_IRQHandler, /* CMP0 interrupt */
    CMP1_IRQHandler, /* CMP1 interrupt */
    CMP2_IRQHandler, /* CMP2 interrupt */
    FTM0_IRQHandler, /* FTM0 fault, overflow and channels interrupt */
    FTM1_IRQHandler, /* FTM1 fault, overflow and channels interrupt */
    FTM2_IRQHandler, /* FTM2 fault, overflow and channels interrupt */
    CMT_IRQHandler, /* CMT interrupt */
    RTC_IRQHandler, /* RTC interrupt */
    Default_Handler, /* Reserved interrupt 83 */
    PIT0_IRQHandler, /* PIT timer channel 0 interrupt */
    PIT1_IRQHandler, /* PIT timer channel 1 interrupt */
    PIT2_IRQHandler, /* PIT timer channel 2 interrupt */
    PIT3_IRQHandler, /* PIT timer channel 3 interrupt */
    PDB0_IRQHandler, /* PDB0 Interrupt */
    USB0_IRQHandler, /* USB0 interrupt */
    USBDCD_IRQHandler, /* USBDCD Interrupt */
    ENET_1588_Timer_IRQHandler, /* Ethernet MAC IEEE 1588 Timer Interrupt */
    ENET_Transmit_IRQHandler, /* Ethernet MAC Transmit Interrupt */
    ENET_Receive_IRQHandler, /* Ethernet MAC Receive Interrupt */
    ENET_Error_IRQHandler, /* Ethernet MAC Error and miscellaneous Interrupt */
    I2S0_IRQHandler, /* I2S0 Interrupt */
    SDHC_IRQHandler, /* SDHC Interrupt */
    DAC0_IRQHandler, /* DAC0 interrupt */
    DAC1_IRQHandler, /* DAC1 interrupt */
    TSI0_IRQHandler, /* TSI0 Interrupt */
    MCG_IRQHandler, /* MCG Interrupt */
    LPTimer_IRQHandler, /* LPTimer interrupt */
    Default_Handler, /* Reserved interrupt 102 */
    PORTA_IRQHandler, /* Port A interrupt */
    PORTB_IRQHandler, /* Port B interrupt */
    PORTC_IRQHandler, /* Port C interrupt */
    PORTD_IRQHandler, /* Port D interrupt */
    PORTE_IRQHandler, /* Port E interrupt */
    Default_Handler, /* Reserved interrupt 108 */
    Default_Handler, /* Reserved interrupt 109 */
    Default_Handler, /* Reserved interrupt 110 */
    Default_Handler, /* Reserved interrupt 111 */
    Default_Handler, /* Reserved interrupt 112 */
    Default_Handler, /* Reserved interrupt 113 */
    Default_Handler, /* Reserved interrupt 114 */
    Default_Handler, /* Reserved interrupt 115 */
    Default_Handler, /* Reserved interrupt 116 */
    Default_Handler, /* Reserved interrupt 117 */
    Default_Handler, /* Reserved interrupt 118 */
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    (void(*)(void)) 0xFFFFFFFF, /* 0x400 Backdoor Comparison Key */
    (void(*)(void)) 0xFFFFFFFF, /* 0x404 Backdoor Comparison Key */
    (void(*)(void)) 0xFFFFFFFF, /* 0x408 FPROT */
    (void(*)(void)) 0xFFFFFFFE  /* 0x40c FSEC, FOPT, FEPROT, FDPROT */
};

