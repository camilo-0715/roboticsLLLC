#include "practica3_improved/StateMachine.hpp"
#include "StateMachinePr3.h"

#include "ros/ros.h"

namespace practica3
{

StateMachine::StateMachine()
{
  
}

bool 
StateMachine::yellow_2_turn()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::blue_2_yellow()
{ 
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::turn_2_ball()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

bool 
StateMachine::ball_2_blue()
{
  return (ros::Time::now() - state_ts_).toSec() > CHANGE_TIME;
}

}