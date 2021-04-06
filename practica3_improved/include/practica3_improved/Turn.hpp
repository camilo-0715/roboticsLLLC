#ifndef PRACTICA3__TURN_HPP__
#define PRACTICA3__TURN_HPP__

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

namespace practica3
{

class Turn: public bica::Component
{
public:
  Turn();
  void step();

private:
  ros::NodeHandle nh_;
  ros::Publisher vel_pub_;
};

} // namespace practica3

#endif // PRACTICA3__TURN_HPP__