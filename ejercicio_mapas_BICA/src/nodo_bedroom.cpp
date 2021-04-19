#include "ejercicio_mapas/bedroom.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bedroom");

  ejercicio_mapas::Bedroom target;

  ros::Rate loop_rate(7);
  
  while(target.ok())
  {
    target.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}