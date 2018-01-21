#ifndef _MOTOR_H_
#define _MOTOR_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "variant.h"
#include "drv_pwm.h"
#include "hw.h"


void motor_init(int freq);
void motor_set(int num,float duty);

#ifdef __cplusplus
}
#endif

#endif
