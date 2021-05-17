#include "proyecto_final/inRoom.hpp"

  /* Comprobar si las coordenadas del punto de partida
     con las del objetivo <- BORRAR
  */

namespace proyecto_final
{

inRoom::inRoom(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), buffer_(), listener_(buffer_) // initialize buffer and listener for tf.
{

}

void
inRoom::setTargetCoords(std::string destination) // assign target depending on destination
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
inRoom::fillRobotPosition()
{
  geometry_msgs::TransformStamped map2bfp; // transform the data from map to bf to obtain robot coords.
  
  try {
    map2bfp = buffer_.lookupTransform("map","base_footprint", ros::Time::now()); 
  } catch (std::exception & e) {
    return;
  } 
  
  tf2::Stamped<tf2::Transform> odom2bf;
  tf2::fromMsg(map2bfp, odom2bf);
  tf2::Vector3 robotVect = odom2bf.getOrigin(); // vector stores the coords, so we take the ones we need.
  actual_x_ = robotVect.getX(); 
  actual_y_ = robotVect.getY();
}

bool
inRoom::isInRoom(){ // used 0.25 as a distance enough to be considered in the room. abs is needed so we always have positive results.
  return ((abs(target_x_ - actual_x_) <= 2) && (abs(target_y_ - actual_y_) <= 2)); 
}

void
inRoom::halt()
{
  ROS_INFO("inRoom halt");
}

BT::NodeStatus
inRoom::tick()
{
  std::string room = getInput<std::string>("room").value(); // get the value from the blackboard

  if (status() == BT::NodeStatus::IDLE)
  {
    ROS_INFO("First time in inRoom");
    setTargetCoords(room.c_str()); // fill the coords the first time
  }
  ros::Duration(0.5).sleep(); // wait 0.5 seconds due to a tf bug
  fillRobotPosition(); // check the position of the robot
  ROS_INFO("Target: [%f, %f], Actual: [%f, %f]", target_x_, target_y_, actual_x_, actual_y_);

  if (isInRoom() == false){ // and return and act accordingly.
    return BT::NodeStatus::FAILURE;
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace proyecto_final
