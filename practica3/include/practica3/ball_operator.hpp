#ifndef BALLOPERATOR_H
#define BALLOPERATOR_H

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/ball_detector.hpp"
#include "practica3/ObjectDetector.hpp"

namespace practica3
{  
  class Ball
  { 
    public:
      Ball();
      int turnTo(ball_detector bdt);
      void step();
      bool hasCollided();


    private:

    ros::NodeHandle n;
    ros::Publisher pub_vel_;

    ObjectDetector odt;
    float movementSpeed = 0.05;
    float turnSpeed = 0.2;
    int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // BALLOPERATOR_H