#include "ejercicio_mapas/movement2.hpp"
#include "ejercicio_mapas/coord_reader.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "emptyroom");

  ejercicio_mapas::CoordReader coord("empty_room");
  ejercicio_mapas::Movement2 emptyroom;

  ros::Rate loop_rate(7);

  while(emptyroom.ok())
  {
    double x = coord.getX();
    double y = coord.getY();

    ROS_INFO("target coordinates: (%f, %f)", x, y);
    emptyroom.moveRobot(x,y,1.0);

    ros::spinOnce();
		loop_rate.sleep();
  }

  return 0;
}
