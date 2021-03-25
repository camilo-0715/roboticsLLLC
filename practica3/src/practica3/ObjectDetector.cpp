#include "practica3/ObjectDetector.hpp"

namespace practica3
{

ObjectDetector::ObjectDetector()
: is_object_(false)
{
  object_pub_ = nh_.advertise<std_msgs::Bool>("obstacle",1);
  laser_sub_ = nh_.subscribe("/scan", 1, &ObjectDetector::laser_callback, this);
}

void
ObjectDetector::laser_callback(const sensor_msgs::LaserScan::ConstPtr msg)
{
  is_object_ = msg->ranges[msg->ranges.size() / 2] < 0.5;
}

bool
ObjectDetector::hasCollided()
{
  return is_object_;
}
    
} //practica3