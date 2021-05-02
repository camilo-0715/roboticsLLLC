#ifndef PROYECTO_FINAL__COORD_READER_HPP__
#define PROYECTO_FINAL__COORD_READER_HPP__

#include "ros/ros.h"
#include <iostream>
#include <map>

namespace proyecto_final
{

class CoordReader
{
  public:
    CoordReader(std::string);
    void setCoord();
    bool placeExists(std::string);
    double getX();
    double getY();
  
  private:
    ros::NodeHandle nh_;
    
    std::string target_name_;
    std::map<std::string,int> targets_;
    enum {BEDROOM = 1, EMPTY_ROOM, GYM, KITCHEN}; 
    
    double coord_x_;
    double coord_y_;

    double origin_x = 0.0;
    double origin_y = 0.0;

    double bedroom_x = 5.811502762329705;
    double bedroom_y = 0.012321041930387383;

    double empty_room_x = 5.922811973070979;
    double empty_room_y = 3.4437645573161837;

    double gym_x = -0.957977527396633;
    double gym_y = -2.7877783015825846;

    double kitchen_x = -6.813386599943721;
    double kitchen_y = 0.9652352103068782;

    double target_orientation_w = 1.0;
};

} // namespace proyecto_final

#endif // PROYECTO_FINAL__COORD_READER_HPP__