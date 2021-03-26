#include "practica3/StateMachine.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica3");

  bica::StateMachinePr3 sm;

  ros::Rate loop_rate(5);

	while(sm.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
  
  return 0;
}