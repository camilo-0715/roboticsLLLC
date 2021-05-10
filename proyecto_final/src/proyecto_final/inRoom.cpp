#include <string>

#include "proyecto_final/inRoom.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

  /* Comprobar si las coordenadas del punto de partida
     con las del objetivo <- BORRAR
  */

namespace proyecto_final
{

inRoom::inRoom(const std::string& name)
: BT::ActionNodeBase(name, {})
{
}

void
inRoom::halt()
{
  ROS_INFO("inRoom halt");
}

BT::NodeStatus
inRoom::tick()
{

  ROS_INFO("inRoom tick");
  
  return BT::NodeStatus::FAILURE;
}

}  // namespace proyecto_final
