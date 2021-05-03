#include "proyecto_final/movement.hpp"

namespace proyecto_final
{
  Movement::Movement() : ac("move_base", true)
  {
      
  }

  void
  Movement::doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result)
  {

  }

  void
  Movement::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
  {

  }

  //this function moves the robot to the coords we give her as parameters
  void
  Movement::moveRobot(double x, double y, double orientation)
  {

  }

} // namespace proyecto_final
