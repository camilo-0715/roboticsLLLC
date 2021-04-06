#include "practica3_improved/BlueGoal.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "blue");  

  practica3::BlueGoal goal;  

  ros::Rate loop_rate(20);

  while(goal.ok())
  {
  	goal.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
