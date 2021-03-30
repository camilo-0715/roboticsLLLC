#ifndef PRACTICA3__YELLOW_GOAL_HPP__
#define PRACTICA3__YELLOW_GOAL_HPP__

#include "practica3_improved/yellowGoal_detector.hpp"
#include "practica3_improved/ObjectDetector.hpp"
#include "bica/Component.h"

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

class YellowGoal: public bica::Component
{
public:
  YellowGoal();
  
  bool isClose();
  int turnTo_IM();
  void move();
  void stop();
  void setTFs();
  int turnTo_TF();
  void step();

private:
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  tf2_ros::StaticTransformBroadcaster broadcaster_;

  ros::NodeHandle n_;
  ros::Publisher pub_vel_;

  ObjectDetector objectDetector_;
  yellowGoal_detector goalDetector_;

  bool first_search;
  bool previous_state;
  bool found;

  geometry_msgs::TransformStamped bf2Goal_2_msg;

  const float MOVEMENT_SPEED = 0.3;
  const float TURN_SPEED = 0.2;
  const int CENTER_SCREEN_COORDS = 300;
};

} // practica3

#endif