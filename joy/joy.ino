#include "ros.h"
#include "geometry_msgs/Twist.h"
#include <RTOS.h>
float value1=0,value2=0;
ros::NodeHandle  nh;

geometry_msgs::Twist joy;
geometry_msgs::Twist pub_joy;

osThreadId thread_id_loop;
osThreadId thread_id_print;


void joy_cb(const geometry_msgs::Twist& msg)
{
  pub_joy = msg;
  value1 = msg.linear.x;
  value2 = msg.linear.y;
}
static void Thread_Loop(void const *argument)
{
  (void) argument;
  ros::Subscriber< geometry_msgs::Twist> joy_sub("/xbox", joy_cb );
  nh.subscribe(joy_sub);
  for(;;)
  {
    loop();
  }
}

static void Thread_print(void const *argument)
{

  ros::Publisher joy_pub("/receive", &pub_joy);
  nh.advertise(joy_pub);
  (void) argument;
  for(;;)
  {
    pub_joy.linear.x = value1;
    pub_joy.linear.y = value2;
    joy_pub.publish(&pub_joy);
   // nh.spinOnce();
   osDelay(30);
  }
}



void  setup()
{
  pinMode(13,OUTPUT);
  pub_joy.linear.x = 0;
  pub_joy.linear.y = 0;
  pub_joy.linear.z = 0;

  pub_joy.angular.x = 0;
  pub_joy.angular.y = 0;
  pub_joy.angular.z = 0;
   nh.getHardware()->setBaud(921600);
  nh.initNode(); 
 
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);

  osThreadDef(THREAD_NAME_PRINT, Thread_print, osPriorityNormal, 0, 1024);
  thread_id_print = osThreadCreate(osThread(THREAD_NAME_PRINT), NULL);
  
  osKernelStart();
}
void  loop()
{ 
 
  digitalWrite(13,!digitalRead(13));
 

	nh.spinOnce();
	osDelay(30);
}
