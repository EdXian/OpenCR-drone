#ifndef _STATETASK_H_
#define _STATETASK_H_
#include "RTOS.h"
#include "variant.h"
#include "drv_pwm.h"
#include "hw.h"
#ifdef __cplusplus
 extern "C" {
#endif
enum{
  safe = 1,
  lpe,
  gps,
  flow,
  stable,
  error,
};
void task(void const *argument);
bool getstatus(uint8_t *state);
bool setstatus(uint8_t state);
#ifdef __cplusplus
}
#endif

#endif
