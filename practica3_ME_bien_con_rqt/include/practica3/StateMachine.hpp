#ifndef PRACTICA3__STATE_MACHINE_HPP__
#define PRACTICA3__STATE_MACHINE_HPP__

#include "StateMachinePr3.h"
#include "ros/ros.h"

#define CHANGE_TIME 30.0

namespace practica3
{

class StateMachine: public bica::StateMachinePr3
{
public:
	StateMachine();
  
  bool yellow_2_turn();
	bool blue_2_yellow();
	bool turn_2_ball();
	bool ball_2_blue();
};

} //practica3

#endif // PRACTICA3__STATE_MACHINE_HPP__