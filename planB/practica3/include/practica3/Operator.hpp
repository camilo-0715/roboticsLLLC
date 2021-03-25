#ifndef PRACTICA3__OPERATOR_HPP__
#define PRACTICA3__OPERATOR_HPP__

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/LaserDetector.hpp"
#include "practica3/Detector.hpp"

namespace practica3
{  
  class Operator
  { 
    public:
      Operator();
      int turnTo(int obj);
      void step(int obj);

    private:
      ros::NodeHandle n;
      ros::Publisher pub_vel_;

      Detector obj_color;
      LaserDetector obj_laser;
      
      float movementSpeed = 0.1;
      float turnSpeed = 0.2;
      int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // PRACTICA3__OPERATOR_HPP__