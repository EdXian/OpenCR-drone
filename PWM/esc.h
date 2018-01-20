#ifndef _ESC_H_
#define _ESC_H_

#include "variant.h"
#include "drv_pwm.h"
#include "hw.h"

#define PINS_COUNT 5




class esc {


public : 
       esc();
  void init();
  void setup(uint32_t ulPin );
  void setvalue();
  void esc_setup(uint32_t ulPin );
private:
  bool     pwm_init[PINS_COUNT];
  int pwm_pins[5] = { 3, 5, 9, 10, 11 };
  TIM_OC_InitTypeDef        OC1;
  TIM_OC_InitTypeDef        OC2;
  TIM_OC_InitTypeDef        OC3;
  TIM_OC_InitTypeDef        OC9;
  TIM_OC_InitTypeDef        OC11;
  TIM_OC_InitTypeDef        OC12;
  
};


#endif




/*
 * #ifdef __cplusplus
 extern "C" {
#endif
 * 
#ifdef __cplusplus
}

#endif
 * 
 * 
 */
