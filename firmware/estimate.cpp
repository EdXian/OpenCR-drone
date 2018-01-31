#include "estimate.h"

QueueHandle_t rpy_queue;
QueueHandle_t rpy_vel_queue;
void estimate_task(void const *argument)
{
   (void) argument;
   cIMU imu;
   bool state;
   px4flow flow;
   vector3 rpy;
   vector3 last_rpy;
   vector3 rpy_vel;
   vector3 last_pose;
   vector3 pose;
   vector3 pose_vel;
  rpy_queue = xQueueCreate( 1, sizeof(vector3) );
  rpy_vel_queue = xQueueCreate( 1, sizeof(vector3) );
  // float last_rpy[3] = {0,0,0};
   imu.begin();
   flow.begin();

     
    while(1){
     imu.update();
     state = flow.compute();
     
     rpy.x = imu.rpy[0];
     rpy.y = imu.rpy[1];
     rpy.z = imu.rpy[2];
     vTaskSuspendAll ();
     xQueueOverwrite(rpy_queue, &rpy );
     xQueueOverwrite(rpy_vel_queue, &rpy_vel );
     xTaskResumeAll (); 
     rpy_vel.x = last_rpy.x - rpy.x;
     rpy_vel.y = last_rpy.y - rpy.y;
     rpy_vel.z = last_rpy.z - rpy.z;
    // pose_vel.z = 
     pose_vel.x = (float)flow.frame.flow_comp_m_x *(1.0) ;
     pose_vel.y = (float)flow.frame.flow_comp_m_y *(1.0) ;
     last_rpy.x = rpy.x;
     last_rpy.y = rpy.y;
     last_rpy.z = rpy.z; 
      
     osDelay(5);
    }
}

  bool get_est_pose(vector3 *pose){
  return (pdTRUE == xQueueReceive( rpy_queue,pose, 0 ));
}


  bool get_est_rpy_vel(vector3 *pose){
  return (pdTRUE == xQueueReceive( rpy_vel_queue,pose, 0 ));
}





