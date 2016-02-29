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
  void init_pll (uint8_t i);
  void init_pll ();  
  void init_hse ();
  void init_hsi ();  
  void Set_frq (uint8_t frq);

};

 
#endif

