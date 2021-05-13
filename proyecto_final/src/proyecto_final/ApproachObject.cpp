#include "proyecto_final/ApproachObject.hpp"

namespace proyecto_final
{

ApproachObject::ApproachObject(const std::string& name, const BT::NodeConfiguration & config) // as we have the inFront node, this should just be a straightforward
: BT::ActionNodeBase(name, config)
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  laser_sub_ = nh_.subscribe("/scan", 1, &ApproachObject::laser_callback, this);
  reached_object = false;
}


void
ApproachObject::laser_callback(const sensor_msgs::LaserScan::ConstPtr msg)
{
  for(int i = (msg->ranges.size() / 2) - 20; i < (msg->ranges.size() / 2) + 20; i++)
  {
    if(msg->ranges[i] < 0.5)
    {
      reached_object = true;
    }
  }
}

void
ApproachObject::move()
{
    geometry_msgs::Twist cmd;

    cmd.linear.x = 0.5;
    ROS_INFO("Move");
    vel_pub_.publish(cmd);

  if (reached_object)
  {
    ROS_INFO("reaches object");
    reached_object = true;
    cmd.linear.x = 0;
    vel_pub_.publish(cmd);
  }

}

void
ApproachObject::halt() // walk to the object. we can use the poincloud to check the distance and not hit it that way.
{
  ROS_INFO("ApproachObject halt");
}

BT::NodeStatus
ApproachObject::tick()
{
  ROS_INFO("Aproach tick");
  move();
  if( reached_object) 
  {
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    return BT::NodeStatus::RUNNING;
  }
  
}
  
}  // namespace proyecto_final
