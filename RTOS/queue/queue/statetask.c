#include "statetask.h"

QueueHandle_t state_queue;
void task(void const *argument)
{
  //pinMode(13,OUTPUT);
  state_queue = xQueueCreate( 1, sizeof( uint8_t ) );
   uint8_t data=0;
  (void) argument;
  while(1){
    data++;
    xQueueOverwrite( state_queue, &data );
    digitalWrite(13,!digitalRead(13));
    osDelay(200);
  }
}

bool getstatus(uint8_t *state){
  return (pdTRUE == xQueueReceive( state_queue, state, 0 ));
}

