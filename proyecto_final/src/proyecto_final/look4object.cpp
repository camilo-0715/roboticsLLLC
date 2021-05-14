#include "proyecto_final/look4object.hpp"

namespace proyecto_final
{

Look4object::Look4object(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), recognizer_(getInput<std::string>("object").value()), buffer_(),listener_(buffer_)
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

void
Look4object::halt() 
{
  ROS_INFO("TurnTo halt");
}

void
Look4object::turn()
{
  cmd_.angular.z = TURN_SPEED;
  vel_pub_.publish(cmd_);
}

void 
Look4object::turnTo_TF()
{
  ROS_INFO("TURN_TO_TF");
  geometry_msgs::Twist cmd;

  geometry_msgs::TransformStamped bf2object_msg;
  try {
    bf2object_msg = buffer_.lookupTransform("base_footprint",getInput<std::string>("object").value(), ros::Time(0));
  } catch (std::exception & e) {
    return;
  }

  double angle = atan2(bf2object_msg.transform.translation.y,bf2object_msg.transform.translation.x);
  ROS_INFO("ANGLE %f", angle);
  if (angle > -ANGLE_INTERVAL && angle < ANGLE_INTERVAL) {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    centered = true;
    vel_pub_.publish(cmd);
  }
  else {
    cmd.linear.x = 0;
    if (angle < 0) {
      cmd.angular.z = -TURN_SPEED;
    } else {
      cmd.angular.z = TURN_SPEED;
    }
    centered = false;
    vel_pub_.publish(cmd);
  }
}

BT::NodeStatus
Look4object::tick()
{
  ROS_INFO("look4object tick");
  if (recognizer_.foundObj()) 
  {
    while (!centered) {
      turnTo_TF();
    }
    return BT::NodeStatus::SUCCESS;
  } 

  turn();
  return BT::NodeStatus::RUNNING;
  
  
}

}  // namespace proyecto_final
