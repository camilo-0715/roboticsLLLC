#ifndef PRACTICA2_DETECTEDODGE_H
#define PRACTICA2_DETECTEDODGE_H

#include "geometry_msgs/Twist.h"
#include "kobuki_msgs/BumperEvent.h"
#include "sensor_msgs/LaserScan.h"
#include "visualization_msgs/MarkerArray.h"

#include "ros/ros.h"

namespace practica2
{
class DetectDodge  
{
  public:
    DetectDodge();
    void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
    void step();
    void initMarkers();

  private:
    ros::NodeHandle n;

    enum movement {GOING_FORWARD = 0, GOING_BACK, TURNING}; 

    const double TURNING_TIME = 3.0;
    const double BACKING_TIME = 3.0;

    const float PI = 3.141592565;
    const double OBSTACLE_DISTANCE = 0.5;
    int state_ = 0;

    bool detect_object_left_;
    bool detect_object_center_;
    bool detect_object_right_;


    ros::Time detect_ts_;
    ros::Time turn_ts_;

    ros::Subscriber sub_laser_;
    ros::Publisher pub_vel_;
    ros::Publisher marker_pub;
};
}

#endif  // PRACTICA2_DETECTEDODGE_H
