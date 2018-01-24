#ifndef _STATETASK_H_
#define _STATETASK_H_
#include "RTOS.h"
#include "variant.h"
#include "drv_pwm.h"
#include "hw.h"
#ifdef __cplusplus
 extern "C" {
#endif

 void task(void const *argument);
bool getstatus(uint8_t *state);

#ifdef __cplusplus
}
#endif

#endif
