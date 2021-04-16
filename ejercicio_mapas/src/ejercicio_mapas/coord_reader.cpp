#include "ejercicio_mapas/coord_reader.hpp"

namespace ejercicio_mapas
{

CoordReader::CoordReader(): nh_("~")
{
  nh_.getParam("name_dest", target_name_);

  targets_["bedroom"]=1;
  targets_["empty_room"]=2;
  targets_["gym"]=3;
  targets_["kitchen"]=4;


  setCoord();
}

void
CoordReader::setCoord() 
{
  int target = targets_[target_name_];

  ROS_INFO("%d", target);


  switch (target) {
    case BEDROOM:
      nh_.getParam("bedroom_x", coord_x_);
      nh_.getParam("bedroom_y", coord_y_);
      break;
    case EMPTY_ROOM:
      nh_.getParam("empty_room_x", coord_x_);
      nh_.getParam("empty_room_y", coord_y_);
      break;
    case GYM:
      nh_.getParam("gym_x", coord_x_);
      nh_.getParam("gym_y", coord_y_);

      ROS_INFO("(%f,%f)", coord_x_, coord_y_);

      break;
    case KITCHEN:
      nh_.getParam("kitchen_x", coord_x_);
      nh_.getParam("kitchen_y", coord_y_);
      break;
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
