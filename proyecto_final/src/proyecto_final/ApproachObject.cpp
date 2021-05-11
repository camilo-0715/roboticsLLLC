#include "proyecto_final/ApproachObject.hpp"

namespace proyecto_final
{

ApproachObject::ApproachObject(const std::string& name, const BT::NodeConfiguration & config) // as we have the inFront node, this should just be a straightforward
: BT::ActionNodeBase(name, config)
{
}

void
ApproachObject::halt() // walk to the object. we can use the poincloud to check the distance and not hit it that way.
{
  ROS_INFO("ApproachObject halt");
}

BT::NodeStatus
ApproachObject::tick()
{
  ROS_INFO("ApproachObject tick");

  // should return running when walking towards it, success when finishes.
  
  return BT::NodeStatus::SUCCESS;
}
  
}  // namespace proyecto_final
