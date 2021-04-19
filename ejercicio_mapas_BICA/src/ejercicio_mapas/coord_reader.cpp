#include "ejercicio_mapas/coord_reader.hpp"

namespace ejercicio_mapas
{

CoordReader::CoordReader(std::string n): nh_("~")
{
  target_name_ = n;

  targets_["bedroom"] = 1;  
  targets_["empty_room"] = 2;
  targets_["gym"] = 3;
  targets_["kitchen"] = 4;

  setCoord();
}

bool
CoordReader::placeExists(std:: string place)
{
  return (place.compare("bedroom") == 0 || place.compare("kitchen") == 0 || place.compare("empty_room") == 0 || place.compare("gym") == 0);
}

void
CoordReader::setCoord() 
{
  if (!placeExists(target_name_)) {
    ROS_INFO("WRONG PARAMETER. GOING TO ORIGIN.");
    coord_x_ = origin_x;
    coord_y_ = origin_y;
    return;
  }
  else {
    int target = targets_[target_name_];

    ROS_INFO("%d", target);

    switch (target) {
      case BEDROOM:
        coord_x_ = bedroom_x;
        coord_y_ = bedroom_y;
        break;
      case EMPTY_ROOM:
        coord_x_ = empty_room_x;
        coord_y_ = empty_room_y;
        break;
      case GYM:
        coord_x_ = gym_x;
        coord_y_ = gym_y;

        break;
      case KITCHEN:
        coord_x_ = kitchen_x;
        coord_y_ = kitchen_y;
        break;
    }
    return;
  }

}

double
CoordReader::getX()
{
  return coord_x_;
}

double
CoordReader::getY()
{
  return coord_y_;
}
}
