#include "MK10D10.h"                 // Device header

#ifndef TACT_H
#define TACT_H


class Tact
{
  //variables
public:
  enum mode {FEI,FBI,BLPI,FEE,FBE,PEE,PBE,BLPE};

 private:
  static uint32_t coreClock;
  static uint16_t busClock;
  static uint16_t flexBusClock;
  static uint16_t flashClock;
  uint8_t src;
  //functions
public:
  Tact ();
  Tact (mode m, uint8_t frq);
  static uint32_t & getCoreClock (){return coreClock;};
  static uint16_t & getBusClock (){return busClock;};
  static uint16_t & getflexBusClock (){return flexBusClock;};
  static uint16_t & getflashClock (){return flashClock;};
private:
  //===int_OSC===//
  //FLL engaged
  void initFEI (uint8_t i);
  //bypass
  void initFBI (uint8_t i);
  //
  void initBLPI (uint8_t i);

  //===ext_OSC===//
  //FLL engaged
  void initFEE (uint8_t i);
  //bypass, FLL engaged
  void initFBE ();
  //PLL engaged
  void initPEE (uint8_t mult=26);
  //bypass, PLL engaged
  void initPBE (uint8_t div=3);
  //bypass
  void initBLPE (uint8_t i);



};

 
#endif

