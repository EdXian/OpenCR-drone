#include "RTOS.h"
#include "statetask.h"
osThreadId thread_id_loop;
osThreadId thread_id_state;
osThreadId thread_id_receive;
uint8_t state_=0;
static void Thread_Loop(void const *argument)
{
  (void) argument;
  for(;;)
  { 
    setstatus(state_);
    Serial.println(state_);
    osDelay(100);
  }
}
static void receive(void const *argument)
{
  (void) argument;

  uint8_t data;
  for(;;)
  {
    if(Serial.available()){
      data = Serial.read();
      data -= 0x30;
    }
    state_ = data;
    osDelay(50);
  }
}
void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);

  osThreadDef(THREAD_NAME_TASK, task, osPriorityNormal, 0, 1024);
  thread_id_state = osThreadCreate(osThread(THREAD_NAME_TASK), NULL);

  osThreadDef(THREAD_NAME_REC, receive, osPriorityNormal, 0, 1024);
  thread_id_receive = osThreadCreate(osThread(THREAD_NAME_REC), NULL);

  osKernelStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
