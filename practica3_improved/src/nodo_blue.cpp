#include "practica3_improved/BlueGoal.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "BlueGoal");  

  practica3::BlueGoal goal;  
  /***********************************************************
  Aqui se podria llamar a los detectores y despues a 
  un metodo que se llame setTFs() por ejemplo que haga guarde
  las trasformada en variables private
  ************************************************************/

  ros::Rate loop_rate(5);

  while(goal.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo haga el giro la 
    primera vez que se reactive 
    if (el estado anterio == !isActive()) {turnTo}
    ***********************************************************/ 

  	goal.step();

  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
