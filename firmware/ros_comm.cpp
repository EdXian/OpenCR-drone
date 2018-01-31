#include "ros_comm.h"

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";



void ros_connect(void const *argument)
{
   (void) argument;
   str_msg.data = hello;
  nh.initNode();
  nh.advertise(chatter);
  pinMode(13,OUTPUT);
  while(1){
    digitalWrite(13,!digitalRead(13));
    chatter.publish(&str_msg);
    nh.spinOnce();
    
    osDelay(4);
  }
}


