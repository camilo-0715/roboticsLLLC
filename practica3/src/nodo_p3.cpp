#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica2");
  ros::NodeHandle n;

  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}