#include "RTOS.h"
#include "ros.h"
#include "IMU.h"
#include "pid.h"
#include "motor.h"
#include "stable.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Byte.h"
#include "sensor_msgs/Imu.h"
//IMU

cIMU    IMU;

//create thread type
osThreadId thread_id_loop;
osThreadId thread_print_status;
osThreadId thread_id_ros_imu;
osThreadId thread_id_ros_joy;
osThreadId thread_id_stable;
//ROS message type

ros::NodeHandle  nh;
std_msgs::Byte status_;
geometry_msgs::Twist joy;                 //xbox one
sensor_msgs::Imu imu_msg;      //imu
geometry_msgs::PoseStamped lpe_pose;      //from optitrack
geometry_msgs::PoseStamped desired_pose ; //



static void Thread_print_status(void const *argument)
{
  (void) argument;
  
  ros::Publisher status_pub("/status", &status_);
  nh.advertise(status_pub);
  for(;;)
  {
    status_.data = 129;
    status_pub.publish(&status_);
    //Serial1.println(status_.data);
    nh.spinOnce();
    osDelay(200);
  }
}

static void Thread_IMU(void const *argument)
{
  (void) argument;
  ros::Publisher imu_pub("/imu", &imu_msg);
  nh.advertise(imu_pub);
  for(;;)
  {
    IMU.update();
   

    imu_msg.header.stamp    = nh.now();
    imu_msg.header.frame_id = "drone";

    imu_msg.angular_velocity.x = IMU.gyroData[0];
    imu_msg.angular_velocity.y = IMU.gyroData[1];
    imu_msg.angular_velocity.z = IMU.gyroData[2];
    imu_msg.angular_velocity_covariance[0] = 0.02;
    imu_msg.angular_velocity_covariance[1] = 0;
    imu_msg.angular_velocity_covariance[2] = 0;
    imu_msg.angular_velocity_covariance[3] = 0;
    imu_msg.angular_velocity_covariance[4] = 0.02;
    imu_msg.angular_velocity_covariance[5] = 0;
    imu_msg.angular_velocity_covariance[6] = 0;
    imu_msg.angular_velocity_covariance[7] = 0;
    imu_msg.angular_velocity_covariance[8] = 0.02;

    imu_msg.linear_acceleration.x = IMU.accData[0];
    imu_msg.linear_acceleration.y = IMU.accData[1];
    imu_msg.linear_acceleration.z = IMU.accData[2];
    imu_msg.linear_acceleration_covariance[0] = 0.04;
    imu_msg.linear_acceleration_covariance[1] = 0;
    imu_msg.linear_acceleration_covariance[2] = 0;
    imu_msg.linear_acceleration_covariance[3] = 0;
    imu_msg.linear_acceleration_covariance[4] = 0.04;
    imu_msg.linear_acceleration_covariance[5] = 0;
    imu_msg.linear_acceleration_covariance[6] = 0;
    imu_msg.linear_acceleration_covariance[7] = 0;
    imu_msg.linear_acceleration_covariance[8] = 0.04;

    imu_msg.orientation.w = IMU.quat[0];
    imu_msg.orientation.x = IMU.quat[1];
    imu_msg.orientation.y = IMU.quat[2];
    imu_msg.orientation.z = IMU.quat[3];

    imu_msg.orientation_covariance[0] = 0.0025;
    imu_msg.orientation_covariance[1] = 0;
    imu_msg.orientation_covariance[2] = 0;
    imu_msg.orientation_covariance[3] = 0;
    imu_msg.orientation_covariance[4] = 0.0025;
    imu_msg.orientation_covariance[5] = 0;
    imu_msg.orientation_covariance[6] = 0;
    imu_msg.orientation_covariance[7] = 0;
    imu_msg.orientation_covariance[8] = 0.0025;

    imu_pub.publish(&imu_msg);
    nh.spinOnce();
    
    /*
    Serial1.print(IMU.rpy[0]);
    Serial1.print("\t");
    Serial1.print(IMU.rpy[1]);
    Serial1.print("\t");
    Serial1.print(IMU.rpy[2]);
    Serial1.println(); 
    */
    osDelay(30);
  }
}

static void Thread_joy(void const *argument)
{
  (void) argument;
  ros::Subscriber< geometry_msgs::Twist> joy_sub("/xbox", joy_cb );
  nh.subscribe(joy_sub);
  float value[6];
  for(;;)
  {
    value[0] = joy.linear.x;
     value[1] = joy.linear.y;
      value[2] = joy.linear.z;
       value[3] = joy.angular.x;
        value[4] = joy.angular.y;
         value[5] = joy.angular.z;

    
    Serial1.print(value[0]);
    Serial1.print("\t");
    Serial1.print(value[1]);
    Serial1.print("\t");
    Serial1.print(value[2]);
    Serial1.print("\t"); 
    Serial1.print(value[3]);
    Serial1.print("\t");
    Serial1.print(value[4]);
    Serial1.print("\t");
    Serial1.print(value[5]);
    Serial1.println(); 
    nh.spinOnce();
    osDelay(20);
  }
}
void joy_cb(const geometry_msgs::Twist& msg)
{
  joy = msg;
  
}


static void Thread_Loop(void const *argument)
{
  (void) argument;
  for(;;)
  {
    loop();
  }
}





void setup() {
  Serial.begin(921600) ;  //ROS Communication
  Serial1.begin(9600)  ;  // Arduino communication
  pinMode(13,OUTPUT);
  IMU.begin();
  
  //initialize();
  nh.initNode(); 
  
  
  
  
 //create task
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);

  osThreadDef(THREAD_NAME_PRINT, Thread_print_status, osPriorityNormal, 0, 1024);
  thread_print_status = osThreadCreate(osThread(THREAD_NAME_PRINT), NULL);

  osThreadDef(THREAD_NAME_IMU, Thread_IMU, osPriorityNormal, 0, 1024);
  thread_id_ros_imu = osThreadCreate(osThread(THREAD_NAME_IMU), NULL);

  osThreadDef(THREAD_NAME_JOY, Thread_joy, osPriorityNormal, 0, 1024);
  thread_id_ros_joy = osThreadCreate(osThread(THREAD_NAME_JOY), NULL);

  osThreadDef(THREAD_NAME_STABLE, task, osPriorityNormal, 0, 1024);
  thread_id_stable = osThreadCreate(osThread(THREAD_NAME_STABLE), NULL);

  
 //start 
  osKernelStart();  //task start
}

void loop() {
  //digitalWrite(13,!digitalRead(13));  // ensure that the system dosent corrupt.
  osDelay(200);
  
}




