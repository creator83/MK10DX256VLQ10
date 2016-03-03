#include "MK10D10.h"                 // Device header

#ifndef TACT_H
#define TACT_H


class tact
{
  //variables
public:
  enum mode {FEI,FBI,BLPI,FEE,FBE,PEE,PBE,BLPE};

 private:
  static uint8_t cpu_clock;
  static uint8_t bus_clock;
  uint8_t src;
  //functions
public:
  tact ();
  tact (mode m, uint8_t frq);
  static uint8_t & get_frq_cpu (){return cpu_clock;};
  static uint8_t & get_frq_bus (){return bus_clock;};
private:
  //===int_OSC===//
  //FLL engaged
  void init_FEI (uint8_t i);
  //bypass
  void init_FBI (uint8_t i);
  //
  void init_BLPI (uint8_t i);

  //===ext_OSC===//
  //FLL engaged
  void init_FEE (uint8_t i);
  //bypass, FLL engaged
  void init_FBE ();
  //PLL engaged
  void init_PEE (uint8_t mult=26);
  //bypass, PLL engaged
  void init_PBE (uint8_t div=3);
  //bypass
  void init_BLPE (uint8_t i);

  void Set_frq (uint8_t frq);

};

 
#endif

