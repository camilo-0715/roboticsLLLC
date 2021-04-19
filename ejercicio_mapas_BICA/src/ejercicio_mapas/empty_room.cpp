#include "ejercicio_mapas/empty_room.hpp"

namespace ejercicio_mapas
{

EmptyRoom::EmptyRoom()
{
  ejercicio_mapas::CoordReader coord("empty_room");

  x_ = coord.getX();
  y_ = coord.getY();

}


void
EmptyRoom::step()
{
  if (!isActive()){
    return;
  } 
  ROS_INFO("target coordinates: (%f, %f)", x_, y_);
  
  ejercicio_mapas::Movement empty_room;
  empty_room.moveRobot(x_,y_,1.0);
 
}  

} // namespace ejercicio_mapas