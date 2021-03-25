#ifndef PRACTICA3__OBJECT_DETECTOR_HPP__
#define PRACTICA3__OBJECT_DETECTOR_HPP__
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "bica/Component.h"

namespace practica3
{

class LaserDetector : public bica::Component
{
public:
  LaserDetector();
  bool isObject();
  
  void step();

private:
  void laser_callback(const sensor_msgs::LaserScan::ConstPtr msg);
  
  ros::NodeHandle nh_;
  ros::Publisher object_pub_;
  ros::Subscriber laser_sub_;

  bool is_object_;
};

} //practica3

#endif // PRACTICA3__OBJECT_DETECTOR_HPP__