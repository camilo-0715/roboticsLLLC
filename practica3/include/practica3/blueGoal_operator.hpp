#ifndef BLUEGOALOPERATOR_H
#define BLUEGOALOPERATOR_H

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/blueGoal_detector.hpp"

namespace practica3
{  
  class BlueGoal
  { 
    public:
      BlueGoal();
      int turnTo(blueGoal_detector bgdt);
      void step();

    private:

    ros::NodeHandle n;
    ros::Publisher pub_vel_;
    float movementSpeed = 0.1;
    float turnSpeed = 0.2;
    int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // BLUEGOALOPERATOR_H