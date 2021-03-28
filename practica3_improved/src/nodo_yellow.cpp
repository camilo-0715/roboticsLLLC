#include "practica3_improved/YellowGoal.hpp"

#include "ros/ros.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "YellowGoal");  

  practica3::YellowGoal goal;  
  /***********************************************************
  Aqui se podria llamar a los detectores y despues a 
  un metodo que se llame setTFs() por ejemplo que haga guarde
  las trasformada en variables private
  ************************************************************/

  bool first_search = true;
  bool previous_state = false; 
  bool found = false;

  ros::Rate loop_rate(5);

  while(goal.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo haga el giro la 
    primera vez que se reactive 
    if (el estado anterio == !isActive()) {turnTo}
    ***********************************************************/ 

  	if (!previous_state && goal.isActive()){
      ROS_INFO("***********************************************************");
      found = false;
    }

    if (!found){
      if (first_search && !goal.turnTo_IM()) {
        ROS_INFO("--------------------------------------------------------------------------");
        found = true;
        first_search = false;
      } else if (!first_search){ //añadir ... && goal.turnTo_TF()) ...
        //found = true;
        ROS_INFO("It's the second search");
      }
    }

    if (found){
      goal.step();
      ROS_INFO("..................................");
      if (goal.isClose()){
        ROS_INFO("It should be making the TFs");
        goal.setTFs();
      }
    }

    previous_state = goal.isActive();

  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
