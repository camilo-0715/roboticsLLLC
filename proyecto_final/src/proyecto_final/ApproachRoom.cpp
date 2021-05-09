#include <string>

#include "proyecto_final/ApproachRoom.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace proyecto_final
{

ApproachRoom::ApproachRoom(const std::string& name)
: BT::ActionNodeBase(name, {})
{
}

void
ApproachRoom::halt()
{
  ROS_INFO("ApproachRoom halt");
}

BT::NodeStatus
ApproachRoom::tick()
{
  ROS_INFO("ApproachRoom tick ");

  return BT::NodeStatus::SUCCESS;
  
}

}  // namespace proyecto_final
