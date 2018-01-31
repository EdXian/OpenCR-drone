#include "stable.h"
 
void stable_task(void const *argument){
  (void) argument;
  vector3 rpy;
  vector3 rpy_vel;
  motor_init(400,2020,1050);  
  motor_unlock();
  motor_set(0,0.0);
  motor_set(1,0.0);
  motor_set(2,0.0);
  motor_set(3,0.0);
  
  while(1){
      
    get_est_pose(&rpy);
    get_est_rpy_vel(&rpy_vel);

     
   osDelay(3); 
  }
}

/*
    Serial.print(rpy.x);
    Serial.print("\t");
    Serial.print(rpy.y);
    Serial.print("\t");
    Serial.print(rpy.z);
    Serial.print("\t");
    
    Serial.print(rpy_vel.x);
    Serial.print("\t");
    Serial.print(rpy_vel.y);
    Serial.print("\t");
    Serial.println(rpy_vel.z);
  */ 

