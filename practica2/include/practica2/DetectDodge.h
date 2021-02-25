#ifndef PRACTICA2_DETECTDODGE_H
#define PRACTICA2_DETECTDODGE_H

#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"

namespace practica2
{
class DetectDodge  
{
  public:
    DetectDodge();
    //DetectDodge(): state_(GOING_FORWARD), pressed_(false);
    void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg);
    void step();
 
  private:
    ros::NodeHandle n_;

    static const int GOING_FORWARD   = 0;
    static const int GOING_BACK   = 1;
    static const int TURNING     = 2;

    int state_;

    bool pressed_;

    ros::Time press_ts_;
    ros::Time turn_ts_;

    ros::Subscriber sub_bumber_;
    ros::Publisher pub_vel_;
};
} // namespace practica2
#endif  // PRACTICA2_DETECTDODGE_H
