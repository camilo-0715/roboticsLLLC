#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ejercicio_mapas");

  if (argv[1] != NULL){
    ejercicio_mapas::CoordReader coord(argv[1]);
    ejercicio_mapas::Movement mov;

    double x = coord.getX();
    double y = coord.getY();

    ROS_INFO("target coordinates: (%f, %f)", x, y);
    mov.moveRobot(x,y,1.0);
  }
  else
  {
    ROS_INFO("ERROR NO ARGS INPUTTED");
  }

  //ros::spin();

  return 0;
}
