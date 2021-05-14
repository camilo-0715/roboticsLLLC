#include "proyecto_final/ApproachObject.hpp"

namespace proyecto_final
{

ApproachObject::ApproachObject(const std::string& name, const BT::NodeConfiguration & config) 
: BT::ActionNodeBase(name, config), buffer_(), listener_(buffer_)
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  reached_object = false;
}

void
ApproachObject::checkDistance(){
  geometry_msgs::TransformStamped map2bfpMsg;
  geometry_msgs::TransformStamped map2ObjectMsg;

  try {
    map2bfpMsg = buffer_.lookupTransform("map","base_footprint", ros::Time(0)); 
  } catch (std::exception & e) {
    ROS_INFO("EXCEPTION BF");
    return;
  } 
  try {
    map2ObjectMsg = buffer_.lookupTransform("map",getInput<std::string>("object").value(), ros::Time(0)); 
  } catch (std::exception & e) {
    ROS_INFO("EXCEPTION OBJ");
    return;
  } 

  tf2::Stamped<tf2::Transform> map2bf;
  tf2::Stamped<tf2::Transform> map2obj;

  tf2::fromMsg(map2bfpMsg, map2bf);
  tf2::fromMsg(map2ObjectMsg, map2obj);

  tf2::Vector3 robotVect = map2bf.getOrigin();
  tf2::Vector3 objectVect = map2obj.getOrigin();

  robot_x = robotVect.getX(); 
  robot_y = robotVect.getY();

  object_x = objectVect.getX(); 
  object_y = objectVect.getY();

  ROS_INFO("[APPROACH OBJECT] ObjectX: %f, ObjectY: %f", object_x, object_y);
  ROS_INFO("[APPROACH OBJECT] RobotX: %f, RobotY: %f", robot_x, robot_y);

  if ((abs(object_x - robot_x) < 0.5) && ((abs(object_y - robot_y) < 0.5))) {
    reached_object = true;
  } else {
    reached_object = false;
  }
}

void
ApproachObject::move()
{
  cmd_.linear.x = 0.5;
  ROS_INFO("[APPROACH OBJECT] Move");
  vel_pub_.publish(cmd_);
}

void
ApproachObject::stop()
{
  ROS_INFO("[APPROACH OBJECT] eaches object");
  cmd_.linear.x = 0;
  vel_pub_.publish(cmd_);
}

void
ApproachObject::halt()
{
  ROS_INFO("ApproachObject halt");
}

BT::NodeStatus
ApproachObject::tick()
{
  ROS_INFO("Approach tick");
  checkDistance();
  if(reached_object) {
    stop();
    return BT::NodeStatus::SUCCESS;
  }
  else {
    move();
    return BT::NodeStatus::RUNNING;
  }
}
  
}  // namespace proyecto_final
