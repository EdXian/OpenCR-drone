#include "statetask.h"
uint8_t get_state=0;
uint8_t last_state=0;
QueueHandle_t state_queue;
int led_pin_user[4] = { BDPIN_LED_USER_1, BDPIN_LED_USER_2, BDPIN_LED_USER_3, BDPIN_LED_USER_4 };
//int led_pin_user[4] ={ BDPIN_GPIO_1  , BDPIN_GPIO_3, BDPIN_GPIO_5, BDPIN_GPIO_7 };

void task(void const *argument)
{
  pinMode(13,OUTPUT);
  pinMode(led_pin_user[0], OUTPUT);
  pinMode(led_pin_user[1], OUTPUT);
  pinMode(led_pin_user[2], OUTPUT);
  pinMode(led_pin_user[3], OUTPUT);
  state_queue = xQueueCreate( 1, sizeof( uint8_t ) );
  get_state = 0;
  (void) argument;
  while(1){
    
    xQueueOverwrite( state_queue, &get_state );
   
    if(last_state != get_state){
      for(int count = 0 ; count<4 ; count++){
        digitalWrite(led_pin_user[count], 1);
      }
    }

    if(get_state == error){
      for(int count = 0 ; count<4 ; count++){
        if(((get_state>>count)&(0x01))){
        
          digitalWrite(led_pin_user[count], !digitalRead(led_pin_user[count]));
        }
     }
    }else{
        for(int count = 0 ; count<4 ; count++){
       digitalWrite(led_pin_user[count], !((get_state>>count)&(0x01)));
     }
    }

   last_state = get_state;
    digitalWrite(13,!digitalRead(13));
    osDelay(200);
  }
}

bool getstatus(uint8_t *state){
  return (pdTRUE == xQueueReceive( state_queue, state, 0 ));
}

bool setstatus(uint8_t state){
  get_state =state;
}

