#include "practica3/LaserDetector.hpp"

#include "ros/ros.h"
#include "bica/Component.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/LaserScan.h"

namespace practica3
{

LaserDetector::LaserDetector()
: is_object_(false)
{
  object_pub_ = nh_.advertise<std_msgs::Bool>("obstacle",1);
  laser_sub_ = nh_.subscribe("/scan", 1, &LaserDetector::laser_callback, this);
}

void
LaserDetector::laser_callback(const sensor_msgs::LaserScan::ConstPtr msg)
{
  is_object_ = msg->ranges[msg->ranges.size() / 2] < 1;
}

bool
LaserDetector::isObject(){
  return is_object_;
}

void
LaserDetector::step()
{
  if (!isActive()) {
    return;
  }

  std_msgs::Bool msg;
  msg.data = is_object_;
  object_pub_.publish(msg);
}
    
} //practica3