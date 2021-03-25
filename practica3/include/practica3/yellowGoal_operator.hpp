#ifndef YELLOWGOALOPERATOR_H
#define YELLOWGOALOPERATOR_H

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/yellowGoal_detector.hpp"

namespace practica3
{  
  class YellowGoal
  { 
    public:
      YellowGoal();
      int turnTo(yellowGoal_detector ygdt);
      void step();

    private:

    ros::NodeHandle n;
    ros::Publisher pub_vel_;
    float movementSpeed = 0.1;
    float turnSpeed = 0.2;
    int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // YELLOWGOALOPERATOR_H