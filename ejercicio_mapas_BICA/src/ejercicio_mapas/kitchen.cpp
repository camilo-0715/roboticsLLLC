#include "ejercicio_mapas/kitchen.hpp"

namespace ejercicio_mapas
{

Kitchen::Kitchen()
{
  ejercicio_mapas::CoordReader coord("kitchen");

  x_ = coord.getX();
  y_ = coord.getY();

}


void
Kitchen::step()
{
  if (!isActive()){
    return;
  } 
  ROS_INFO("target coordinates: (%f, %f)", x_, y_);
  
  ejercicio_mapas::Movement kitchen;
  kitchen.moveRobot(x_,y_,1.0);

}  

} // namespace part2