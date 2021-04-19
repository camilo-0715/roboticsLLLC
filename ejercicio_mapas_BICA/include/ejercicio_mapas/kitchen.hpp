#ifndef PRACTICA3__KITCHEN_HPP__
#define PRACTICA3__KITCHEN_HPP__

#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include "ros/ros.h"

#include "bica/Component.h"

namespace ejercicio_mapas
{

class Kitchen: public bica::Component
{
  public:
    Kitchen();
    void step();

  private:
    ros::NodeHandle n_;

    double x_;
    double y_;

};

} // namespace part2

#endif // PRACTICA3__KITCHEN_HPP__