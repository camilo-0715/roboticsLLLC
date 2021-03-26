#include "practica3/StateMachine.hpp"
#include "StateMachinePr3.h"

#include "ros/ros.h"

namespace practica3
{

StateMachine::StateMachine()
{
  addDependency("Ball");
}

bool 
StateMachine::yellow_2_turn()
{
  removeDependency("YellowGoal");
  addDependency("Turn"); 
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::blue_2_yellow()
{
  removeDependency("BlueGoal");
  addDependency("YellowGoal");  

  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::turn_2_ball()
{
  removeDependency("Turn");
  addDependency("Ball");  

  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::ball_2_blue()
{
  removeDependency("Ball");
  addDependency("BlueGoal");  
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

}