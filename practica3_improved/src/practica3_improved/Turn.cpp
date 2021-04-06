#include "practica3_improved/Turn.hpp"

#include "bica/Component.h"
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
  if (!isActive()){
    return;
  }

  // Depuración luego se quita
  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist msg;
  msg.angular.z = 0.5;
  vel_pub_.publish(msg);
}
    
} // namespace practica3