#ifndef PRACTICA3__YELLOW_GOAL_HPP__
#define PRACTICA3__YELLOW_GOAL_HPP__

#include "practica3/yellowGoal_detector.hpp"

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <ctime>

namespace practica3
{

class YellowGoal: public bica::Component
{
public:
  YellowGoal();
  
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

#endif // PRACTICA3__YELLOW_GOAL_HPP__