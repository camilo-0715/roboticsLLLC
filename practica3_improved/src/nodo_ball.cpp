#include "practica3_improved/Ball.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Ball");  

  practica3::Ball ball; 

  ros::Rate loop_rate(5);
  while(ball.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo detecte la pelota
    y haga el giro la primera vez que se reactive 
    if (el estado anterio == !isActive()) {setCoord();turnTo();}
    ***********************************************************/
     
    ball.step();

  	ros::spinOnce();

  	loop_rate.sleep();
  }  

  return 0;
}
