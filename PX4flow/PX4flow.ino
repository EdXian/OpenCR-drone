#include "I2Cdev.h"
#include "px4flow.h"

//int16_t height;
//px4flow_frame frame;
//I2Cdev px4flow;
//uint8_t data[22];
bool state;
px4flow flow;
void setup() {
  // put your setup code here, to run once:

pinMode(13,1);
//px4flow.begin(100);
Serial.begin(115200);
flow.begin();
}
px4flow_frame frame;
void loop() {
  
  state = flow.compute_integral();
  
  if(!state){
    Serial.println("error");
  }

  Serial.println(flow.integral_frame.ground_distance);
 
   

    digitalWrite(13,!digitalRead(13));
   delay(10);
}
