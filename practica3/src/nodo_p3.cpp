#include "ros/ros.h"
#include "practica3/blueGoal_detector.hpp"
#include "practica3/ball_detector.hpp"
#include "practica3/yellowGoal_detector.hpp"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica3");
  ros::NodeHandle n;
  practica3::ball_detector bdt;
  practica3::yellowGoal_detector ygdt;
  practica3::blueGoal_detector bgdt;

  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    ros::spinOnce();
    ROS_INFO("ball x: %d", bdt.getBallX());
    ROS_INFO("ball y: %d", bdt.getBallY());

    ROS_INFO("yellow goal x: %d", ygdt.getYGoalX());
    ROS_INFO("yellow goal y: %d", ygdt.getYGoalY());

    ROS_INFO("blue goal x: %d", bgdt.getBGoalX());
    ROS_INFO("blue goal y: %d", bgdt.getBGoalY());
    loop_rate.sleep();
  }
  
  return 0;
}