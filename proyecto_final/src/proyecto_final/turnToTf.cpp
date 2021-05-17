#include "proyecto_final/turnToTf.hpp"

namespace proyecto_final
{

turnToTf::turnToTf(const std::string& name, const BT::NodeConfiguration & config) // implemented this to check if an object is in front of another.
: BT::ActionNodeBase(name, config), buffer_(),listener_(buffer_) // it should have a method called turnToTf that returns a boolean and just checks the alignment of the TF with it.
{
  pub_vel_=  nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

int 
turnToTf::turnTo_TF()
{
  geometry_msgs::Twist cmd;

  geometry_msgs::TransformStamped bf2object_msg;
  try {
    bf2object_msg = buffer_.lookupTransform("base_footprint",getInput<std::string>("object").value(), ros::Time(0));
  } catch (std::exception & e) {
    return -1;
  }

  double angle = atan2(bf2object_msg.transform.translation.y,bf2object_msg.transform.translation.x);
  
  if (angle > -ANGLE_INTERVAL && angle < ANGLE_INTERVAL) {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    pub_vel_.publish(cmd);
    return 0;
  }
  else {
    cmd.linear.x = 0;
    if (angle < 0) {
      cmd.angular.z = -TURN_SPEED;
    } else {
      cmd.angular.z = TURN_SPEED;
    }
    pub_vel_.publish(cmd);
    return 1;
  }
}



/*
  Bool
  turnToTf::isturnToTf(){
    return robotTf.get angle.... - object.getangle...
  }
*/
void
turnToTf::halt()
{
  ROS_INFO("turnToTf halt");
}

BT::NodeStatus
turnToTf::tick()
{

  ROS_INFO("turnToTf tick");
  if( turnTo_TF() == 0) 
  {
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    return BT::NodeStatus::RUNNING;
  }
  
}

}  // namespace proyecto_final
