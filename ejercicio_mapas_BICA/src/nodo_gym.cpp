#include "ejercicio_mapas/gym.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gym");

  ejercicio_mapas::Gym target;

  ros::Rate loop_rate(7);
  
  while(target.ok())
  {
    target.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
