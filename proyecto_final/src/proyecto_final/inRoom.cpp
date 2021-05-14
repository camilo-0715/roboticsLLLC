#include "proyecto_final/inRoom.hpp"

namespace proyecto_final
{

InRoom::InRoom(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), buffer_(), listener_(buffer_)
{
  movebase_sub_ = nh_.subscribe("move_base_msgs/MoveBaseFeedback", 1, &InRoom::feedbackCb, this);
}

void
InRoom::setTargetCoords(std::string destination) 
{
  if (destination.compare("bedroom") == 0){
      target_x_ = bedroom_x;
      target_y_ = bedroom_y;
  }
  else if (destination.compare("empty_room") == 0){
      target_x_ = empty_room_x;
      target_y_ = empty_room_y;
  }   
  else if (destination.compare("gym") == 0){
      target_x_ = gym_x;
      target_y_ = gym_y;
  }
  else if (destination.compare("kitchen") == 0){
      target_x_ = kitchen_x;
      target_y_ = kitchen_y;
  }
  else
  {
    ROS_INFO("NO VALID TARGET INPUTTED");
    target_x_ = 0;
    target_y_ = 0;
  }
}

void 
InRoom::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{
  actual_x_ = feedback->base_position.pose.position.x;
  actual_y_ = feedback->base_position.pose.position.y;
}

bool
InRoom::isInRoom()
{ 
  return ((abs(target_x_ - actual_x_) <= 2) && (abs(target_y_ - actual_y_) <= 2)); 
}

void
InRoom::halt()
{
  ROS_INFO("InRoom halt");
}

BT::NodeStatus
InRoom::tick()
{
  std::string room = getInput<std::string>("room").value();

  if (status() == BT::NodeStatus::IDLE)
  {
    ROS_INFO("First time in InRoom");
    setTargetCoords(room.c_str()); 
  }
  ros::Duration(0.5).sleep(); 
  ROS_INFO("[IN ROOM] Target: [%f, %f], Actual: [%f, %f]", target_x_, target_y_, actual_x_, actual_y_);

  if (!isInRoom()){ 
    return BT::NodeStatus::FAILURE;
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace proyecto_final
