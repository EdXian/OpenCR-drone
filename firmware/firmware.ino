#include "system.h"

osThreadId thread_led_task;
osThreadId thread_system;
osThreadId thread_estimate;
osThreadId thread_stable;
static void system_task(void const *argument)
{
   (void) argument;
    Serial.begin(921600);
  while(1){
   loop();
  }
}

void setup(){

  osThreadDef(THREAD_NAME_LED,  led_task,  osPriorityNormal, 0, 1024);
  thread_led_task = osThreadCreate(osThread(THREAD_NAME_LED), NULL);
  
  osThreadDef(THREAD_NAME_SYS,  system_task,  osPriorityNormal, 0, 1024);
  thread_system = osThreadCreate(osThread(THREAD_NAME_SYS), NULL);

  osThreadDef(THREAD_NAME_EST,  estimate_task,  osPriorityNormal, 0, 1024);
  thread_estimate = osThreadCreate(osThread(THREAD_NAME_EST), NULL);

  osThreadDef(THREAD_NAME_STABLE,  stable_task,  osPriorityNormal, 0, 1024);
  thread_stable = osThreadCreate(osThread(THREAD_NAME_STABLE), NULL);
  
  osKernelStart();
}


void loop(){
  //Serial.println("system");
  osDelay(400);
}

