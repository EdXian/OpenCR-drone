#include "stable.h"


void task(void const *argument)
{
  (void) argument;
  while(1){
   digitalWrite(13,!digitalRead(13));
    osDelay(1000);
  }
}
