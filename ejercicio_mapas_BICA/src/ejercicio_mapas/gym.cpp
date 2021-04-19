#include "ejercicio_mapas/gym.hpp"

namespace ejercicio_mapas
{

Gym::Gym()
{
  ejercicio_mapas::CoordReader coord("gym");
  
  x_ = coord.getX();
  y_ = coord.getY();
}


void
Gym::step()
{
  if (!isActive()){
    return;
  }
  ROS_INFO("target coordinates: (%f, %f)", x_, y_);
  
  ejercicio_mapas::Movement gym;
  gym.moveRobot(x_,y_,1.0);
 
}  

} // namespace part2