#include "practica3_improved/YellowGoal.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "yellow");  

  practica3::YellowGoal goal;  

  ros::Rate loop_rate(20);

  while(goal.ok())
  {
    goal.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
