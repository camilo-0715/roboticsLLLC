#include "practica2/Pr2Class.h"

#include "ros/ros.h"

namespace practica2
{

  Pr2Class::Pr2Class(): state_(GOING_FORWARD), pressed_(false)
  {
    // sub_bumber_ = n_.subscribe(...);
    // pub_vel_ = n_.advertise<...>(...)
  }

  void Pr2Class::bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
  {
    // pressed_ = (...);

    //  ...
  }

  void Pr2Class::step()
  {
    geometry_msgs::Twist cmd;

    switch (state_)
    {
    case GOING_FORWARD:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;
      if (pressed_)
      {
        press_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }
      break;

    case GOING_BACK:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;

      if ((ros::Time::now() - press_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        state_ = TURNING;
        ROS_INFO("GOING_BACK -> TURNING");
      }
      break;

    case TURNING:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;
      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING -> GOING_FORWARD");
      }
      break;
    }

    // pub_vel_.publish(...);
  }



}