#include "practica3/Turn.hpp"

#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turn");
  ros::NodeHandle n;

  practica3::Turn turn;

  ros::Rate loop_rate(20);

  while (turn.ok())
  {
    turn.step();

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
