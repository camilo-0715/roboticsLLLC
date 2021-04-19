#ifndef PRACTICA3__BEDROOM_HPP__
#define PRACTICA3__BEDROOM_HPP__

#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include "ros/ros.h"

#include "bica/Component.h"

namespace ejercicio_mapas
{

class Bedroom: public bica::Component
{
  public:
    Bedroom();
    void step();

  private:
    ros::NodeHandle n_;

    double x_;
    double y_;

};

} // namespace ejercicio_mapas

#endif // PRACTICA3__BEDROOM_HPP__