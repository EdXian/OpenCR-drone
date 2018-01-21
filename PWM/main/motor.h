#ifndef _MOTOR_H_
#define _MOTOR_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "variant.h"
#include "drv_pwm.h"
#include "hw.h"

typedef struct {
  int freq;
  int high;
  int low ;
} motor_profile;
void motor_init(int freq , int High , int Low);
//void motor_init(motor_profile *profile);
void motor_set(int num,float duty);

#ifdef __cplusplus
}
#endif

#endif
