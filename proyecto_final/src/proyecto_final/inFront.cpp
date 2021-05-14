#include "proyecto_final/inFront.hpp"

namespace proyecto_final
{

InFront::InFront(const std::string& name, const BT::NodeConfiguration & config) 
: BT::ActionNodeBase(name, config)
{
  obj_sub_ = nh_.subscribe("/darknet_ros/bounding_boxes", 1, &InFront::darknetCB, this);
}

void 
InFront::darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
  int i = 0;
  std::string item = getInput<std::string>("object").value();
  found = false;
  int num_classes = msg->bounding_boxes.size();

  while (i < num_classes && !found) {
    if (msg->bounding_boxes[i].Class == item.c_str() && msg->bounding_boxes[i].probability > 0.5) {
      found = true;
    }
    i++;
  } 
}

bool
InFront::isInFront()
{
  return found;
}

void
InFront::halt()
{
  ROS_INFO("inFront halt");
}

BT::NodeStatus
InFront::tick()
{
  ROS_INFO("inFront tick");
  if (isInFront()) {
    return BT::NodeStatus::SUCCESS;
  }
  else {
    return BT::NodeStatus::FAILURE;
  }
  
}

}  // namespace proyecto_final
