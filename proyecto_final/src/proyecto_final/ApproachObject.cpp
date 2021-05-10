#include <string>

#include "proyecto_final/ApproachObject.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"


/* Uso de TFs para girar colocandose completamente frente al objeto
   y avanzar cuando alcance la posicion buscada devuelve success 
   si no ha llegado devuelve running y si no se puede alcanzar devuelve
   failure <-BORRAR
*/

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

  
  return BT::NodeStatus::SUCCESS;
}
  
}  // namespace proyecto_final
