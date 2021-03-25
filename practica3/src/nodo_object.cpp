#include "practica3/ObjectDetector.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "object_detector");
  ros::NodeHandle n;

  practica3::ObjectDetector object_detector;

  ros::Rate loop_rate(20);

  while (object_detector.ok())
  {
    object_detector.step();

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
