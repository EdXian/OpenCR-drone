
#include "motor.h"
#include <RTOS.h>
#define PWM_PIN 6

#define motor1_set(x) motor_set(0,x);
#define motor2_set(x) motor_set(1,x);
#define motor3_set(x) motor_set(2,x);
#define motor4_set(x) motor_set(3,x);
osThreadId thread_id_pwm;
osThreadId thread_id_loop;
int pins[5]={3,5,9,10,11};
int led_pin = 13;
float i=0;


static void Thread_PWM(void const *argument)
{
   (void) argument;

  
  for(;;)
  {
    Serial.print("RTOS Cnt : ");
    Serial.println(i++);
    digitalWrite(led_pin, !digitalRead(13));  // set to as HIGH LED is turn-off
    osDelay(100);
   
  }
}

static void Thread_Loop(void const *argument)
{
  (void) argument;  
  motor_unlock();

  for(;;)
  {
    loop();
  }
}


void setup() {
   Serial.begin(115200); 
  motor_init(400,2020,1050);  //set cutoff value
 pinMode(13,OUTPUT);
 

 osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_PWM, Thread_PWM,  osPriorityNormal, 0, 1024);
 
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);
  thread_id_pwm = osThreadCreate(osThread(THREAD_NAME_PWM), NULL);
  osKernelStart();
}

float j=0;
void loop() {
  if(j>0.98){
    j=0.1;
    osDelay(2000);
  }else{
    j+=0.01;
  }
  motor1_set(0.2);
  motor2_set(0.3);
  motor3_set(0.3);
  motor4_set(0.3);
 
  osDelay(100);  
}

