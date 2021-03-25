#ifndef BLUEGOALOPERATOR_H
#define BLUEGOALOPERATOR_H

#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include "practica3/blueGoal_detector.hpp"
#include "practica3/ObjectDetector.hpp"

#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"

#include "geometry_tf/transforms.h"


namespace practica3
{  
  class BlueGoal
  { 
    public:
      BlueGoal();
      int turnTo(blueGoal_detector bgdt);
      void step();
      bool hasCollided();
      void setTF();

    private:

    ros::NodeHandle n;
    ros::Publisher pub_vel_;
    ObjectDetector odt;

    float movementSpeed = 0.2;
    float turnSpeed = 0.2;
    int CENTER_SCREEN_COORDS = 300;
  };
}

#endif // BLUEGOALOPERATOR_H