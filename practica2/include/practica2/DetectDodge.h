#ifndef PRACTICA2_DETECTDODGE_H
#define PRACTICA2_DETECTDODGE_H

#include "geometry_msgs/Twist.h"
#include "kobuki_msgs/BumperEvent.h"
#include "sensor_msgs/LaserScan.h"

#include "ros/ros.h"

namespace practica2
{
class DetectDodge  
{
  public:
    DetectDodge();
    void bumperCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
    void step();
 
  private:
    ros::NodeHandle n_;

    static const int GOING_FORWARD   = 0;
    static const int GOING_BACK   = 1;
    static const int TURNING     = 2;

    int state_;

    bool pressed_;

    ros::Time press_ts_;
    ros::Time turn_ts_;

    ros::Subscriber sub_laser_;
    ros::Publisher pub_vel_;
};
} // namespace practica2
#endif  // PRACTICA2_DETECTDODGE_H
