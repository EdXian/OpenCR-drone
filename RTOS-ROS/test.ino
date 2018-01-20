#include <RTOS.h>
#include <ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include <sensor_msgs/Imu.h>
#include "std_msgs/Header.h"
#include "sensor_msgs/Joy.h"
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <IMU.h>



osThreadId thread_id_loop;
osThreadId thread_id_led;
osThreadId thread_id_ros ;
osThreadId thread_id_rosimu ;
osThreadId thread_id_sub;
osThreadId thread_id_sub2;
osThreadId thread_id_joy;
sensor_msgs::Joy joy;
geometry_msgs::Pose pose;
ros::NodeHandle  nh;
geometry_msgs::PoseStamped poset;
std_msgs::Header header , last_header , d_header;
static void Thread_Loop(void const *argument)
{
  (void) argument;


  for(;;)
  {
    loop();
  }
}

static void Thread_joy(void const *argument){
(void) argument;

 ros::Subscriber<sensor_msgs::Joy> joy_sub("/joy", &joy_cb);
  nh.subscribe(joy_sub);
  for(; ;){
  nh.spinOnce();
  osDelay(10);
  }
}

static void Thread_sub2(void const *argument){
(void) argument;
 ros::Publisher header2("/poset", &poset);
 nh.advertise(header2);

  for(; ;){
  poset.header.frame_id="opencr";
  poset.header.stamp = nh.now();
  header2.publish(&poset);
  osDelay(10);
  }
}

static void Thread_sub(void const *argument)
{
  (void) argument;

  ros::Subscriber<geometry_msgs::Pose> sub("/pose", &pose_cb);
  nh.subscribe(sub);
  
 
  
  ros::Publisher pose2("/pose2", &pose);
  nh.advertise(pose2);
  
 
  for(;;)
  {
    
    
   
    pose2.publish(&pose);
    
    osDelay(10); 
  }
}
void pose_cb(const geometry_msgs::Pose& msg){
  pose = msg;
}
float value1 , value2;
void joy_cb(const sensor_msgs::Joy& msg){
  joy = msg;

  value1 = msg.axes[0];
  value2 = msg.axes[1];
}


static void ros_Loop(void const *argument)
{
  (void) argument;
   std_msgs::String str_msg;
  
  nh.initNode();
  ros::Publisher chatter("chatter", &str_msg);
  nh.advertise(chatter);

  
  char hello[13] = "hello world!";
  for(;;)
  {
    str_msg.data = hello;
    chatter.publish( &str_msg );

    nh.spinOnce();
   osDelay(100); 
  }
}

static void rosimu_Loop(void const *argument)
{
  (void) argument;
  
   
    
    sensor_msgs::Imu imu_msg;
    ros::Publisher imu_pub("imu", &imu_msg);
    
    
    geometry_msgs::TransformStamped tfs_msg;
    tf::TransformBroadcaster tfbroadcaster;
    
    cIMU imu;
     nh.initNode();
  nh.advertise(imu_pub);
  tfbroadcaster.init(nh);

  imu.begin();
  
  for(;;)
  {
  
    imu.update();
    
    
    imu_msg.header.stamp    = nh.now();
    imu_msg.header.frame_id = "imu_link";

  imu_msg.angular_velocity.x = imu.gyroData[0];
  imu_msg.angular_velocity.y = imu.gyroData[1];
  imu_msg.angular_velocity.z = imu.gyroData[2];
    
    // Serial.print(imu_msg.angular_velocity.x);
    // Serial.print("\t");
    // Serial.print(imu_msg.angular_velocity.y);
//     Serial.print("\t");
    // Serial.print(imu_msg.angular_velocity.z);
    // Serial.print("\n");


//    Serial.print(imu.rpy[0]);
//     Serial.print("\t");
//     Serial.print(imu.rpy[1]);
//     Serial.print("\t");
//     Serial.print(imu.rpy[2]);
//     Serial.print("\n");

    imu_msg.angular_velocity_covariance[0] = 0.02;
    imu_msg.angular_velocity_covariance[1] = 0;
    imu_msg.angular_velocity_covariance[2] = 0;
    imu_msg.angular_velocity_covariance[3] = 0;
    imu_msg.angular_velocity_covariance[4] = 0.02;
    imu_msg.angular_velocity_covariance[5] = 0;
    imu_msg.angular_velocity_covariance[6] = 0;
    imu_msg.angular_velocity_covariance[7] = 0;
    imu_msg.angular_velocity_covariance[8] = 0.02;

    imu_msg.linear_acceleration.x = imu.accData[0];
    imu_msg.linear_acceleration.y = imu.accData[1];
    imu_msg.linear_acceleration.z = imu.accData[2];
    imu_msg.linear_acceleration_covariance[0] = 0.04;
    imu_msg.linear_acceleration_covariance[1] = 0;
    imu_msg.linear_acceleration_covariance[2] = 0;
    imu_msg.linear_acceleration_covariance[3] = 0;
    imu_msg.linear_acceleration_covariance[4] = 0.04;
    imu_msg.linear_acceleration_covariance[5] = 0;
    imu_msg.linear_acceleration_covariance[6] = 0;
    imu_msg.linear_acceleration_covariance[7] = 0;
    imu_msg.linear_acceleration_covariance[8] = 0.04;

    imu_msg.orientation.w = imu.quat[0];
    imu_msg.orientation.x = imu.quat[1];
    imu_msg.orientation.y = imu.quat[2];
    imu_msg.orientation.z = imu.quat[3];

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

    tfs_msg.header.stamp    = nh.now();
    tfs_msg.header.frame_id = "base_link";
    tfs_msg.child_frame_id  = "imu_link";
    tfs_msg.transform.rotation.w = imu.quat[0];
    tfs_msg.transform.rotation.x = imu.quat[1];
    tfs_msg.transform.rotation.y = imu.quat[2];
    tfs_msg.transform.rotation.z = imu.quat[3];

    tfs_msg.transform.translation.x = 0.0;
    tfs_msg.transform.translation.y = 0.0;
    tfs_msg.transform.translation.z = 0.0;

    tfbroadcaster.sendTransform(tfs_msg);
   
  nh.spinOnce();
   osDelay(33);
  }
}






void setup() 
{
  //Serial.begin(115200);
  nh.getHardware()->setBaud(921600);
  // define thread
  osThreadDef(THREAD_NAME_LOOP, Thread_Loop, osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_LED,  Thread_Led,  osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_SUB,  Thread_sub,  osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_ROS,  ros_Loop,  osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_ROS_IMU ,  rosimu_Loop,  osPriorityNormal, 0, 1024);
    osThreadDef(THREAD_NAME_SUB2,  Thread_sub2,  osPriorityNormal, 0, 1024);
 osThreadDef(THREAD_NAME_JOY,  Thread_joy,  osPriorityNormal, 0, 1024);
  // create thread
  thread_id_loop = osThreadCreate(osThread(THREAD_NAME_LOOP), NULL);
  thread_id_led  = osThreadCreate(osThread(THREAD_NAME_LED), NULL);
  thread_id_ros  = osThreadCreate(osThread(THREAD_NAME_ROS), NULL);
  thread_id_rosimu  = osThreadCreate(osThread(THREAD_NAME_ROS_IMU), NULL);
  thread_id_sub =  osThreadCreate(osThread(THREAD_NAME_SUB), NULL);
   thread_id_sub2 =  osThreadCreate(osThread(THREAD_NAME_SUB2), NULL);
   thread_id_joy =  osThreadCreate(osThread(THREAD_NAME_JOY), NULL);
  
  // start kernel
  //Mahony_Init(&Mahony ,250.0, 0.1,0.05 ); //Mahony
  osKernelStart();

}

void loop() 
{
  static uint32_t cnt = 0;
   
 Serial.print(value1);
 Serial.print("\t");
 Serial.print(value2);
  Serial.print("\n");
  osDelay(100);  
}

static void Thread_Led(void const *argument)
{
  (void) argument;


  pinMode(13, OUTPUT);

  for(;;)
  {
    digitalWrite(13, !digitalRead(13));
    osDelay(300);
  }
}

