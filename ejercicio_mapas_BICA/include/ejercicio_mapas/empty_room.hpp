#ifndef PRACTICA3__EMPTY_ROOM_HPP__
#define PRACTICA3__EMPTY_ROOM_HPP__

#include "ejercicio_mapas/movement.hpp"
#include "ejercicio_mapas/coord_reader.hpp"
#include "ros/ros.h"

#include "bica/Component.h"

namespace ejercicio_mapas
{

class EmptyRoom: public bica::Component
{
  public:
    EmptyRoom();
    void step();

  private:
    ros::NodeHandle n_;

    double x_;
    double y_;
};

} // namespace ejercicio_mapas

#endif // PRACTICA3__EMPTY_ROOM_HPP__