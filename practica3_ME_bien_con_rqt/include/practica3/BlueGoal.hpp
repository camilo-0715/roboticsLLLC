#ifndef PRACTICA3__BLUE_GOAL_HPP__
#define PRACTICA3__BLUE_GOAL_HPP__

#include "practica3/blueGoal_detector.hpp"

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"

namespace practica3
{

class BlueGoal: public bica::Component
{
public:
  BlueGoal();

  void setTFs();

  
  void turnTo();
  void step();

private:
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  tf2_ros::StaticTransformBroadcaster broadcaster;

  ros::NodeHandle n;
  ros::Publisher pub_vel_;
};

} //practica3

#endif // PRACTICA3__BLUE_GOAL_HPP__