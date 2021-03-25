#ifndef PRACTICA3__OBJECT_DETECTOR_HPP__
#define PRACTICA3__OBJECT_DETECTOR_HPP__
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "bica/Component.h"
#include "std_msgs/Bool.h"



namespace practica3
{

class ObjectDetector
{
public:
  ObjectDetector();
  
  bool hasCollided();

private:
  void laser_callback(const sensor_msgs::LaserScan::ConstPtr msg);
  
  ros::NodeHandle nh_;
  ros::Publisher object_pub_;
  ros::Subscriber laser_sub_;

  bool is_object_;
};

} //practica3

#endif // PRACTICA3__OBJECT_DETECTOR_HPP__