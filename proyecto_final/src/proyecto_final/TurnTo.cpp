#include "proyecto_final/TurnTo.hpp"

namespace proyecto_final
{

TurnTo::TurnTo(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), recognizer_(getInput<std::string>("object").value())
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  tf_set = false;
}

void
TurnTo::halt() 
{
  ROS_INFO("TurnTo halt");
}

void
TurnTo::turn()
{
  geometry_msgs::Twist msg;
  msg.angular.z = -0.2;
  vel_pub_.publish(msg);
}

void
TurnTo::stop()
{
  geometry_msgs::Twist msg;
  msg.angular.z = 0.0;
  vel_pub_.publish(msg);
}

BT::NodeStatus
TurnTo::tick()
{
  if (tf_set)
    return BT::NodeStatus::SUCCESS;
    
  ROS_INFO("TurnTo tick");
  turn();

  if (recognizer_.foundObj()) 
  {
    stop();
    tf_set = true;
    return BT::NodeStatus::SUCCESS;
  } 
  else 
  {
    return BT::NodeStatus::RUNNING;
  }
  
}

}  // namespace proyecto_final
