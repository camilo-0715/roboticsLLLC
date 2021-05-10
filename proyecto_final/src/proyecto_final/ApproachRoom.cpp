#include <string>

#include "proyecto_final/ApproachRoom.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

/* Hace uso de coord_reader y movement para desplazarse hasta la 
   habitacion que se pida devuelve success si se ha llegado a la
   habitacion running si aun no se ha llegado y failure si no se 
   puede llegar <-BORRAR
*/

namespace proyecto_final
{

ApproachRoom::ApproachRoom(const std::string& name)
: BT::ActionNodeBase(name, {})
{
}

/*
void 
ApproachRoom::init( const std::string& room)
{
  room_ = room;
}*/

void
ApproachRoom::halt()
{
  ROS_INFO("ApproachRoom halt");
}

BT::NodeStatus
ApproachRoom::tick()
{
  ROS_INFO("ApproachRoom tick");

  return BT::NodeStatus::SUCCESS;
  
}

}  // namespace proyecto_final
