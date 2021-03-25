#include "practica3/LaserDetector.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laser_detector");
  ros::NodeHandle n;

  practica3::LaserDetector laser_detector;

  ros::Rate loop_rate(20);

  while (laser_detector.ok())
  {
    laser_detector.step();

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
