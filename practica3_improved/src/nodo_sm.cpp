#include "practica3_improved/StateMachinePr3.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica3");

  bica::StateMachinePr3 sm;

  ros::Rate loop_rate(20);

	while(sm.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
  
  return 0;
}