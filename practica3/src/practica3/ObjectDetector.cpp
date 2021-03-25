#include "practica3/ObjectDetector.hpp"

#include "ros/ros.h"
#include "bica/Component.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/LaserScan.h"

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
  is_object_ = msg->ranges[msg->ranges.size() / 2] < 1;
}

void
ObjectDetector::step()
{
  if (!isActive()) {
    return;
  }

  std_msgs::Bool msg;
  msg.data = is_object_;
  object_pub_.publish(msg);
}
    
} //practica3