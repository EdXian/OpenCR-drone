#ifndef _PX4FLOW_H_
#define _PX4FLOW_H_
#include "variant.h"
#include "I2Cdev.h"
#define PX4FLOW_ADDRESS 0x42
#define PX4_FRAME_ADDR 0x00
#define PX4_INTEGRAL_FRAME_ADDR 0x16

#define FRAME_LENGTH 22
#define INTEGRAL_FRAME_LENGTH 26
#define PX4FLOW_TIMEOUT 10

typedef struct i2c_frame
{
    uint16_t frame_count;// counts created I2C frames
    int16_t pixel_flow_x_sum;// accumulated x flow in pixels*10 since last I2C frame
    int16_t pixel_flow_y_sum;// accumulated y flow in pixels*10 since last I2C frame
    int16_t flow_comp_m_x;// x velocity*1000 in meters / timestep
    int16_t flow_comp_m_y;// y velocity*1000 in meters / timestep
    int16_t qual;// Optical flow quality / confidence 0: bad, 255: maximum quality
    int16_t gyro_x_rate; //gyro x rate
    int16_t gyro_y_rate; //gyro y rate
    int16_t gyro_z_rate; //gyro z rate
    uint8_t gyro_range; // gyro range
    uint8_t sonar_timestamp;// timestep in milliseconds between I2C frames
    int16_t ground_distance;// Ground distance in meters*1000. Positive value: distance known. Negative value: Unknown distance
} px4flow_frame;

typedef struct i2c_integral_frame
{
    uint16_t frame_count_since_last_readout;//number of flow measurements since last I2C readout [#frames]
    int16_t pixel_flow_x_integral;//accumulated flow in radians*10000 around x axis since last I2C readout [rad*10000]
    int16_t pixel_flow_y_integral;//accumulated flow in radians*10000 around y axis since last I2C readout [rad*10000]
    int16_t gyro_x_rate_integral;//accumulated gyro x rates in radians*10000 since last I2C readout [rad*10000] 
    int16_t gyro_y_rate_integral;//accumulated gyro y rates in radians*10000 since last I2C readout [rad*10000] 
    int16_t gyro_z_rate_integral;//accumulated gyro z rates in radians*10000 since last I2C readout [rad*10000] 
    uint32_t integration_timespan;//accumulation timespan in microseconds since last I2C readout [microseconds]
    uint32_t sonar_timestamp;// time since last sonar update [microseconds]
    int16_t ground_distance;// Ground distance in meters*1000 [meters*1000]
    int16_t gyro_temperature;// Temperature * 100 in centi-degrees Celsius [degcelsius*100]
    uint8_t quality;// averaged quality of accumulated flow values [0:bad quality;255: max quality]
}  px4flow_integral_frame;

class px4flow
{
  public:
  px4flow();
  void begin();
  bool compute();
  bool compute_integral();
  uint16_t get_frame_count();
  uint16_t get_vel_x();
  uint16_t get_vel_y();

  uint16_t get_sum_x();
  uint16_t get_sum_y();

  uint16_t detect_quality();
  
  uint16_t get_gyro_x();
  uint16_t get_gyro_y();
  uint16_t get_gyro_z();

  uint16_t get_distance();
  
  px4flow_frame frame;
  px4flow_integral_frame integral_frame;
  
  
  private:
  uint8_t data[26];
  bool iic_state;
  
 // px4flow_integral_frame integral_frame;
};




#endif
