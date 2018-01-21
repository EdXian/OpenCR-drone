
#include "motor.h"

#define PWM_PIN 6
#include <RTOS.h>
osThreadId thread_id_pwm;
osThreadId thread_id_loop;
int pins[5]={3,5,9,10,11};
int led_pin = 13;

static void Thread_PWM(void const *argument)
{
   (void) argument;

  int i=0; 
  for(;;)
  {
    if(i<100) {
      i++;
    }else{
      i=0;
    }
    for(int j=0;j<5;j++)
   
    //motor_set(j,i*0.01);
    osDelay(10);
  }
}

static void Thread_Loop(void const *argument)
{
  (void) argument;


  for(;;)
  {
    loop();
  }
}


void setup() {
   Serial.begin(115200);
  motor_init(400);
 pinMode(13,OUTPUT);
 

 osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_PWM, Thread_PWM,  osPriorityNormal, 0, 1024);
 
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);
  thread_id_pwm = osThreadCreate(osThread(THREAD_NAME_PWM), NULL);
  osKernelStart();
}
int i=0;
void loop() {
 
  motor_set(0,(i%100)*0.01);
     Serial.print("RTOS Cnt : ");
  Serial.println(i++);
  digitalWrite(led_pin, !digitalRead(13));  // set to as HIGH LED is turn-off
  osDelay(100);  
 
}

