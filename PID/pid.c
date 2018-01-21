#include "pid.h"

#include "math.h"


void pid_init(PID_Type *data ,float p,float i ,float d , float dt , 
                                float upper_limit,float lower_limit,float init_state)
{
  data->error = 0.0;
  data->last_error=0.0;
  data->last_state=0.0;
  data->desired_state = 0.0;
  data->integral=0.0;
  data->deriv = 0.0;
  data->kp = p ;
  data->ki = i ;
  data->kd = d ;
  data->dt = dt ;
  data->actual_state = init_state;
  data->output_upper_limit = upper_limit;
  data->output_lower_limit = lower_limit;
}


float pid_compute(PID_Type *data,float cmd,float state){
  float output=0.0;
  float error = 0.0;
  data->desired_state = cmd;
  data->actual_state=state;
  error = ( data->desired_state - data->actual_state);
  data->error = ( data->desired_state -data->actual_state);

  data->integral += (data->error * data->dt) ; 
  data->deriv = (data->error - data->last_error) /data->dt;
  
  
  
  output = data->kp * error + data->ki * data->integral + data->kd * data->deriv;

  //output =  pid_cutoff(output ,data->output_upper_limit ,data->output_lower_limit);

  data->last_error = data->error;
  data->last_state = data->actual_state;
  return output;
}


float pid_cutoff(float data,float upper , float lower){
  float value=0.0;
  value = data;
  if(data > upper){
    value = upper;
  }
  if(data<upper){
    value = lower;
  }
  return value;
}




