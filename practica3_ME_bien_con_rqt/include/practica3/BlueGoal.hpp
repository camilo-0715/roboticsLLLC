#ifndef PRACTICA3__BLUE_GOAL_HPP__
#define PRACTICA3__BLUE_GOAL_HPP__

#include "practica3/blueGoal_detector.hpp"

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <ctime>

namespace practica3
{

class BlueGoal: public bica::Component
{
public:
  BlueGoal();

  /************************************************
  void setTFs(valores obtenidos de los detectores)
  {
    establece los valores de las TFs
  }
  **************************************************/
  
  void turnTo();
  void step();

private:
  /***************
  Las trasformadas
  ****************/

  ros::NodeHandle n;
  ros::Publisher pub_vel_;
};

} //practica3

#endif // PRACTICA3__BLUE_GOAL_HPP__