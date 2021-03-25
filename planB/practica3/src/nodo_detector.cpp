#include "ctime"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "bica/Component.h"
#include "practica3/Detector.hpp"
#include "practica3/Turn.hpp"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "detector");
  ros::NodeHandle n;

  practica3::Detector obj;


  ros::Rate loop_rate(20);

  obj.setObj(1);
  while (ros::ok())
  {
    ros::spinOnce();

    ROS_INFO("ball x: %d", obj.getX());
    ROS_INFO("ball y: %d", obj.getY());

    ROS_INFO("blue goal x: %d", obj.getX());
    ROS_INFO("blue goal y: %d", obj.getY());

    ROS_INFO("yellow goal x: %d", obj.getX());
    ROS_INFO("yellow goal y: %d", obj.getY());

    loop_rate.sleep();
  }
  
  return 0;
}