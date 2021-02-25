#include "ros/ros.h"
#include "practica2/DetectDodge.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica2");
  ros::NodeHandle n;

  practica2::DetectDodge bumpgo;

  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    bumpgo.step();

    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}