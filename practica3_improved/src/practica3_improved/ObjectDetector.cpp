#include "practica3_improved/ObjectDetector.hpp"

namespace practica3
{

ObjectDetector::ObjectDetector()
: is_object_(false)
{
  laser_sub_ = nh_.subscribe("/scan", 1, &ObjectDetector::laser_callback, this);
}

void
ObjectDetector::laser_callback(const sensor_msgs::LaserScan::ConstPtr msg)
{
  is_object_ = msg->ranges[msg->ranges.size() / 2] < 0.7; // centro del laser, distancia 0.7
}

bool
ObjectDetector::hasCollided()
{
  return is_object_;
}
    
} // namespace practica3