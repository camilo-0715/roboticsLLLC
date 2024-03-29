#ifndef PRACTICA3__BLUE_GOAL_HPP__
#define PRACTICA3__BLUE_GOAL_HPP__

#include "practica3_improved/ColorDetector.hpp"
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

  class BlueGoal: public bica::Component
  {
  public:
    BlueGoal();

    bool isClose();
    void turnTo_IM();
    int turnTo_TF();
    void moveForward();
    void stop();
    void setTFs();
    void step();

  private:
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;
    tf2_ros::StaticTransformBroadcaster broadcaster_;

    ros::NodeHandle n_;
    ros::Publisher pub_vel_;

    ObjectDetector objectDetector_;
    ColorDetector goalDetector_;

    bool tfSet;
    bool found;

    const int ANGLE_COORDS = 100;
    const int BLUE_NUMBER = 1;
    const float ANGLE_INTERVAL = 0.05;
    const float MOVEMENT_SPEED = 0.37;
    const float TURN_SPEED = 0.27;
    const int CENTER_SCREEN_COORDS = 314;
  };

} // namespace practica3

#endif // PRACTICA3__BLUE_GOAL_HPP__