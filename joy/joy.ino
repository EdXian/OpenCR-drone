#include "ros.h"
#include "sensor_msgs/Joy.h"


sensor_msgs::Joy joy;
float value1,value2;
ros::NodeHandle  nh;

void joy_cb(const sensor_msgs::Joy& msg)
{
	joy = msg;
	value1 = joy.axes[0];
	value2 = joy.axes[1];
}


void  setup()
{
  nh.getHardware()->setBaud(921600);
	nh.initNode();
	ros::Subscriber<sensor_msgs::Joy> joy_sub("joy", joy_cb );	
	nh.subscribe(joy_sub);

}

void  loop()
{
	
//	Serial.print(value1);
//	Serial.print("\t");
//	Serial.print(value2);
//	Serial.print("\n");
//
//  delay(10);
	nh.spinOnce();
	delay(10);
}
