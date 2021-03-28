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
  //int turnTo_TF();
  void setTFs();
  void step();

private:
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  tf2_ros::StaticTransformBroadcaster broadcaster;

  geometry_msgs::TransformStamped bf2Goal_2_msg;

  ros::NodeHandle n;
  ros::Publisher pub_vel_;

  ObjectDetector odt;
  yellowGoal_detector ygdt;

  float movementSpeed = 0.05;
  float turnSpeed = 0.2;
  int CENTER_SCREEN_COORDS = 300;

};

} // practica3

#endif