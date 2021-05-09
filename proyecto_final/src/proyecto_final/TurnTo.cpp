#include <string>

#include "proyecto_final/TurnTo.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace proyecto_final
{

TurnTo::TurnTo(const std::string& name)
: BT::ActionNodeBase(name, {})
{
}

void
TurnTo::halt()
{
  ROS_INFO("TurnTo halt");
}

BT::NodeStatus
TurnTo::tick()
{
  ROS_INFO("TurnTo tick");

  return BT::NodeStatus::SUCCESS;
}

}  // namespace proyecto_final
