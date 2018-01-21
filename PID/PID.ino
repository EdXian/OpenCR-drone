#include <RTOS.h>
#include "pid.h"
osThreadId thread_id_loop;
osThreadId thread_id_pid;
#define stamp 0.1 
typedef struct{
  float x ; //state x
  float vx ; //
  float coeffA; 
  float dt;
}ball;

ball ball1;
PID_Type pid;

float cmd=10, out=0.0;
int incomingByte = 0;

void ball_dynamics(ball *data ,float input){
  data->vx =  data->coeffA *  data->x + input;
  data->x = data->x + data->vx * data->dt; 
}

static void Thread_Loop(void const *argument)
{
  (void) argument;
  for(;;)
  {
    loop();
  }
 
}



static void Thread_pid(void const *argument)
{
  (void) argument;
  int i=0;
  for(;;)
  {
    
    out = pid_compute(&pid , cmd , ball1.x);
    ball_dynamics(&ball1,out);
    cmd = 10+cos(i*0.01);
    Serial.print(cmd);
    Serial.print("\t");
    Serial.println(ball1.x);
    i++;
   osDelay(100);
  }
 
}


void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  
  ball1.vx = 0;
  ball1.x =0;
  ball1.coeffA = -0.1;
  ball1.dt = stamp ;
   
  ball_dynamics(&ball1,0);
  pid_init(&pid , 0.4 , 0.3, 0.4 ,stamp,100,-100,0);
  
  osThreadDef(THREAD_NAME_PID, Thread_pid, osPriorityNormal, 0, 1024);
  thread_id_pid = osThreadCreate(osThread(THREAD_NAME_PID), NULL);
  
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);
  osKernelStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,!digitalRead(13));
  osDelay(30);
}
