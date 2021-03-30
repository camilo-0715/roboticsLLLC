#ifndef PRACTICA3__BALL_HPP__
#define PRACTICA3__BALL_HPP__

#include "practica3_improved/ball_detector.hpp"
#include "practica3_improved/ObjectDetector.hpp"

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

#include "bica/Component.h"

namespace practica3
{

class Ball: public bica::Component
{
  public:
    Ball();
    int turnTo_IM();
    bool isClose();
    void setTFs();
    void move();
    int turnTo_TF();
    void step();
    void stop();

  private:

    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;
    tf2_ros::StaticTransformBroadcaster broadcaster_;

    ros::NodeHandle n_;
    ros::Publisher pub_vel_;

    ObjectDetector objectDetector_;
    ball_detector ballDetector_;

    geometry_msgs::TransformStamped bf2Ball_2_msg;

    bool first_search;
    bool previous_state; 
    bool found;

    const float MOVEMENT_SPEED = 0.1;
    const float TURN_SPEED = 0.2;
    const int CENTER_SCREEN_COORDS = 300;
    const int BALL_DETECTABLE_HEIGHT = 470; 

};

} //practica3

#endif // PRACTICA3__BALL_HPP__