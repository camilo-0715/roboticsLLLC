#ifndef PRACTICA3__BALL_HPP__
#define PRACTICA3__BALL_HPP__

#include "practica3/ball_detector.hpp"

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <ctime>

namespace practica3
{

class Ball: public bica::Component
{
  public:
    Ball();
    
    /************************************************
    void setCoord(valores obtenidos de los detectores)
    {
      establece los valores de las TFs
    }
    **************************************************/
    void turnTo();
    void step();

  private:
    /******************************************
    variables con las coordenadas de la pelota
    *******************************************/

    ros::NodeHandle n;
    ros::Publisher pub_vel_;
};

} //practica3

#endif // PRACTICA3__BALL_HPP__