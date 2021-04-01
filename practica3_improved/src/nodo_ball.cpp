#include "practica3_improved/Ball.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ball");  

  practica3::Ball ball; 

  ros::Rate loop_rate(20);
  while(ball.ok())
  {
    ball.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
