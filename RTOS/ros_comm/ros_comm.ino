#include "RTOS.h"
#include "ros_comm.h"
osThreadId thread_id_loop;


void setup() {
  // put your setup code here, to run once:
     osThreadDef(THREAD_NAME_STABLE, ros_connect, osPriorityNormal, 0, 1024);
     thread_id_loop = osThreadCreate(osThread(THREAD_NAME_STABLE), NULL);
     osKernelStart();
}

void loop() {
  // put your main code here, to run repeatedly:

}
