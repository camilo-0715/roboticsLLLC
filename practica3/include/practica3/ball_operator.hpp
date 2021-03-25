#ifndef BALLOPERATOR_H
#define BALLOPERATOR_H

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/ball_detector.hpp"

namespace practica3
{  
  class Ball
  { 
    public:
      Ball();
      int turnTo(ball_detector bdt);
      void step();

    private:

    ros::NodeHandle n;
    ros::Publisher pub_vel_;
    float movementSpeed = 0.1;
    float turnSpeed = 0.2;
    int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // BALLOPERATOR_H