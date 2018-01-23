#ifndef _PID_H_
#define _PID_H_

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct{

float kp;
float ki;
float kd;

float desired_state;
float actual_state;
float last_state;
float error;
float last_error;

float integral;
float deriv;

float output_upper_limit;
float output_lower_limit;
float dt;
}PID_Type;

//init
void pid_init(PID_Type *data ,float p,float i ,
float d , float dt , float upper_limit,float lower_limit,float init_state);

float pid_compute(PID_Type *data,float cmd,float state);
float pid_cutoff(float data,float upper , float lower);

#ifdef __cplusplus
}
#endif



#endif
