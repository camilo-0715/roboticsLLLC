#include "ejercicio_mapas/movement2.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include "ros/ros.h"
int main(int argc, char **argv)
{
  ros::init(argc, argv, "bedroom");

  ejercicio_mapas::CoordReader coord("bedroom");
  ejercicio_mapas::Movement2 bedroom;

  ros::Rate loop_rate(7);

  while (ros::ok())
  {
    double x = coord.getX();
    double y = coord.getY();

    ROS_INFO("target coordinates: (%f, %f)", x, y);
    bedroom.moveRobot(x,y,1.0);

    ros::spinOnce();
		loop_rate.sleep();
  }

  return 0;
}