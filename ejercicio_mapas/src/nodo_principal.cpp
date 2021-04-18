#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ejercicio_mapas");

  ejercicio_mapas::CoordReader coord(argv[1]);
  ejercicio_mapas::Movement mov;

  double x = coord.getX();
  double y = coord.getY();

  ROS_INFO("target coordinates: (%f, %f)", x, y);
  mov.moveRobot(x,y,1.0);

  //ros::spin();

  return 0;
}
