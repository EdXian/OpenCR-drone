#include "px4flow.h"


I2Cdev px4flow_iic;
px4flow::px4flow(){
  
 
}
void px4flow::begin(){
   px4flow_iic.begin(100);
}

bool px4flow::compute(){

  
  iic_state = px4flow_iic.readBytes( PX4FLOW_ADDRESS,PX4_FRAME_ADDR,FRAME_LENGTH,data,PX4FLOW_TIMEOUT);
  
  if(!iic_state){
    return false;
//    // return false;
//    Serial.println("update error");
  }else{
    frame.frame_count = data[0]|(data[1]<<8);
  frame.pixel_flow_x_sum  = data[2]|(data[3]<<8);
  frame.pixel_flow_y_sum  = data[4]|(data[5]<<8);
  frame.flow_comp_m_x     = data[6]|(data[7]<<8);
  frame.flow_comp_m_y     = data[8]|(data[9]<<8);
  frame.qual              =data[10]|(data[11]<<8);
  frame.gyro_x_rate       =  data[12]|(data[13]<<8);
  frame.gyro_y_rate       =  data[14]|(data[15]<<8);
  frame.gyro_z_rate       =  data[16]|(data[17]<<8);
  frame.gyro_range        =  data[18];
  frame.sonar_timestamp   = data[19];
  frame.ground_distance   = data[20]|(data[21]<<8);
  return true;
  }
  
}

bool   px4flow::compute_integral(){

  iic_state = px4flow_iic.readBytes( PX4FLOW_ADDRESS,PX4_INTEGRAL_FRAME_ADDR,INTEGRAL_FRAME_LENGTH,data,PX4FLOW_TIMEOUT);
   if(!iic_state){
    return false;
//    // return false;
//    Serial.println("update error");
  }
  else{
    integral_frame.frame_count_since_last_readout =data[0]|(data[1]<<8);
  integral_frame.pixel_flow_x_integral  = data[2]|(data[3]<<8);
  integral_frame.pixel_flow_y_integral  = data[4]|(data[5]<<8);
  integral_frame.gyro_x_rate_integral   = data[6]|(data[7]<<8);
  integral_frame.gyro_y_rate_integral   = data[8]|(data[9]<<8);
  integral_frame.gyro_z_rate_integral   = data[10]|(data[11]<<8);
  integral_frame.integration_timespan   = (data[12]|(data[13]<<8))|((data[14]|(data[15]<<8))<<8);
  integral_frame.sonar_timestamp        = (data[16]|(data[17]<<8))|((data[18]|(data[19]<<8))<<8);
  integral_frame.ground_distance        = data[20]|(data[21]<<8);
  integral_frame.gyro_temperature       = data[22]|(data[23]<<8);
  integral_frame.quality                = data[24];
   return true;
  }
  

 
}




uint16_t px4flow::get_distance(){
  //return frame.ground_distance;
}

uint16_t px4flow::get_vel_x(){
 // return frame.flow_comp_m_x ;
}

uint16_t px4flow::get_vel_y(){
 // return frame.flow_comp_m_y ;
}

uint16_t px4flow::get_gyro_x(){
  //return  frame.gyro_x_rate ;
}



