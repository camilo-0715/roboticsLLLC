#include <string>

#include "proyecto_final/ApproachObject.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace proyecto_final
{

ApproachObject::ApproachObject(const std::string& name)
: BT::ActionNodeBase(name, {})
{
}

void
ApproachObject::halt()
{
  ROS_INFO("ApproachObject halt");
}

BT::NodeStatus
ApproachObject::tick()
{
  ROS_INFO("ApproachObject tick");

  /*Podria llamar a movement y que devuelva success
    cuando haya alcanzado la posicion frente al objeto,
    running mientras está buscando y failure cuando no 
    consiga alcanzarla
  */
  return BT::NodeStatus::SUCCESS;
}
  
}  // namespace proyecto_final
