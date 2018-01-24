#include "RTOS.h"
#include "statetask.h"
osThreadId thread_id_loop;
osThreadId thread_id_state;
static void Thread_Loop(void const *argument)
{
  (void) argument;
  
  uint8_t data;
  for(;;)
  {
    getstatus(&data);
    Serial.println(data);
    osDelay(100);
  }
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);

  osThreadDef(THREAD_NAME_TASK, task, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_TASK), NULL);
  
  osKernelStart();
}

void loop() {
  // put your main code here, to run repeatedly:

}
