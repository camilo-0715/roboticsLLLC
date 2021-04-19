#include "ejercicio_mapas/kitchen.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "kitchen");

  ejercicio_mapas::Kitchen target;

  ros::Rate loop_rate(7);
  
  while(target.ok())
  {
    target.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
