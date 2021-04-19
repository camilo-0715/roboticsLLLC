#include "ejercicio_mapas/part2_state_machine.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "part2");

  ejercicio_mapas::Movement2 sm;

  ros::Rate loop_rate(20);

	while(sm.ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}

  return 0;
} 