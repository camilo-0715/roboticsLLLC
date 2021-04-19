#ifndef PRACTICA3__GYM_HPP__
#define PRACTICA3__GYM_HPP__

#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include "ros/ros.h"

#include "bica/Component.h"

namespace ejercicio_mapas
{

class Gym: public bica::Component
{
  public:
    Gym();
    void step();

  private:
    ros::NodeHandle n_;

    double x_;
    double y_;
};

} // namespace ejercicio_mapas

#endif // PRACTICA3__GYM_HPP__