#include "practica3/Turn.hpp"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

namespace practica3
{

Turn::Turn()
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

void
Turn::step()
{

  ROS_INFO("GIRANDO");

  geometry_msgs::Twist msg;
  msg.angular.z = 0.2;
  msg.linear.x = 0;
  vel_pub_.publish(msg);
}
    
} //practica3