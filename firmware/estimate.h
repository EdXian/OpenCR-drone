#ifndef _ESTIMATE_H_
#define _ESTIMATE_H_
#include "RTOS.h"
#include "IMU.h"
#include "px4flow.h"
#include "led.h"
//#define px4flow_enable 
 typedef struct {
  float x;
  float y;
  float z;
} vector3;
void estimate_task(void const *argument);
bool get_est_pose(vector3 *pose);
bool get_est_rpy_vel(vector3 *pose);
#endif
