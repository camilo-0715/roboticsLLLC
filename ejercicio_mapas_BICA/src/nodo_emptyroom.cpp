#include "ejercicio_mapas/empty_room.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "emptyroom");

  ejercicio_mapas::EmptyRoom target;

  ros::Rate loop_rate(7);
  
  while(target.ok())
  {
    target.step();
  	ros::spinOnce();
  	loop_rate.sleep();
  }  

  return 0;
}
