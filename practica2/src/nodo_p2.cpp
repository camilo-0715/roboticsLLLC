#include "practica2/Pr2Class.h"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica2");
  ros::NodeHandle n;

  Pr2Class bumpgo;

  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    bumpgo.step();

    ros::spinOnce();
    loop_rate.sleep();
  }
  

  return 0;
}