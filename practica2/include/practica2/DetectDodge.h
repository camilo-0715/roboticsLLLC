#ifndef PRACTICA2_DETECTEDODGE_H
#define PRACTICA2_DETECTEDODGE_H

#include "geometry_msgs/Twist.h"
#include "kobuki_msgs/BumperEvent.h"
#include "sensor_msgs/LaserScan.h"

#include "ros/ros.h"

namespace practica2
{
class DetectDodge  
{
  public:
    DetectDodge();
    void bumperCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
    void step();

  private:
    ros::NodeHandle n;

    static const int GOING_FORWARD   = 0;
    static const int GOING_BACK   = 1;
    static const int TURNING     = 2;

    const double TURNING_TIME = 5.0; //esto hay que mirarlo solo hepuesto una cifra para que no de error de compilacion
    const double BACKING_TIME = 5.0;

    int state_;

    bool detect_object_;

    ros::Time detect_ts_;
    ros::Time turn_ts_;

    ros::Subscriber sub_laser_;
    ros::Publisher pub_vel_;
};
}

#endif  // PRACTICA2_DETECTEDODGE_H
