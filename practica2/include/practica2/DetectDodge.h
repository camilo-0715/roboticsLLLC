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
      void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
      void step();

    private:
      ros::NodeHandle n;

      enum movement {GOING_FORWARD = 0, GOING_BACK, TURNING}; // habría que hacer 2 giros distintos TURNING_L y TURNING_R, de momento lo dejo así para ir provando

      /*
      static const int GOING_FORWARD   = 0;
      static const int GOING_BACK   = 1;
      static const int TURNING     = 2;
      */

      const double TURNING_TIME = 1.0; //esto hay que mirarlo solo hepuesto una cifra para que no de error de compilacion
      const double BACKING_TIME = 3.0;

      const double OBSTACLE_DISTANCE = 0.5;
      int state_ = 0;

      bool detect_object_left_;
      bool detect_object_center_;
      bool detect_object_right_;


      ros::Time detect_ts_;
      ros::Time turn_ts_;

      ros::Subscriber sub_laser_;
      ros::Publisher pub_vel_;
  };
}

#endif  // PRACTICA2_DETECTEDODGE_H
