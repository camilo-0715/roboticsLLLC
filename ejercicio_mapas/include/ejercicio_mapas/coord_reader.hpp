#ifndef EJERCICIO_MAPAS__COORD_READER_HPP__
#define EJERCICIO_MAPAS__COORD_READER_HPP__

#include "ros/ros.h"
#include <iostream>
#include <map>

namespace ejercicio_mapas
{

class CoordReader
{
  public:
    CoordReader();
    
    void setCoord();
    double getX();
    double getY();
  
  private:
    ros::NodeHandle nh_;
    
    std::string target_name_;
    std::map<std::string,int> targets_;
    enum {BEDROOM = 1, EMPTY_ROOM, GYM, KITCHEN}; 
    
    double coord_x_;
    double coord_y_;
};

} // namespace ejercicio_mapas

#endif // EJERCICIO_MAPAS__COORD_READER_HPP__