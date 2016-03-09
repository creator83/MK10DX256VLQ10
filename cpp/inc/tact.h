#include "MK10D10.h"                 // Device header

#ifndef TACT_H
#define TACT_H


class tact
{
  //variables
public:
  enum src_tact {HSI,LSI,HSE,LSE};
 private:
  static uint8_t f_cpu;
  uint8_t src;
  //functions
public:
  tact (uint8_t frq , src_tact s );
  tact ();
  tact (src_tact s);
  static uint8_t & get_frq (){return f_cpu;};
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
  void init_FBE (uint8_t div=0);
  //PLL engaged
  void init_PEE (uint8_t i);
  //bypass, PLL engaged
  void init_PBE (uint8_t i);
  //bypass
  void init_BLPE (uint8_t i);


  void init_hse ();
  void init_hsi ();  
  void Set_frq (uint8_t frq);

};

 
#endif

