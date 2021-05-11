#include "proyecto_final/inFront.hpp"

namespace proyecto_final
{

inFront::inFront(const std::string& name, const BT::NodeConfiguration & config) // implemented this to check if an object is in front of another.
: BT::ActionNodeBase(name, config) // it should have a method called inFront that returns a boolean and just checks the alignment of the TF with it.
{
}

/*
  Bool
  inFront::isInFront(){
    return robotTf.get angle.... - object.getangle...
  }
*/
void
inFront::halt()
{
  ROS_INFO("inFront halt");
}

BT::NodeStatus
inFront::tick()
{

  ROS_INFO("inFront tick");
  // if .... in Front... return BT::NodeStatus::SUCESS;
  // else FAILURE
  return BT::NodeStatus::FAILURE;
}

}  // namespace proyecto_final
