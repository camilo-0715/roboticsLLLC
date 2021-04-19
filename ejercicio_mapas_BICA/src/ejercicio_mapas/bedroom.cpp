#include "ejercicio_mapas/bedroom.hpp"

namespace ejercicio_mapas
{

Bedroom::Bedroom()
{
  ejercicio_mapas::CoordReader coord("bedroom");
  
  x_ = coord.getX();
  y_ = coord.getY();

}


void
Bedroom::step()
{
  if (!isActive()){
    return;
  } 

  ROS_INFO("target coordinates: (%f, %f)", x_, y_);
  
  ejercicio_mapas::Movement bedroom;
  bedroom.moveRobot(x_,y_,1.0);
  
}  

} // namespace ejercicio_mapas