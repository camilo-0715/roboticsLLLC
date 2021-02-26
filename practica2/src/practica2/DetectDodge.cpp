#include "practica2/DetectDodge.h"

namespace practica2
{

DetectDodge::DetectDodge()
: state_(GOING_FORWARD), detect_object_(false)
{
  sub_laser_ = n.subscribe("/scan", 1, &DetectDodge::bumperCallback, this); //camilo: estoy hay que cambiarlo para subscribirse al laser en vez de al buumper
  // pub_vel_ = n_.advertise<...>(...)
  pub_vel_ = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

}

void 
DetectDodge::bumperCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  // detect_object_ = (...); //aqui hay

  //  ...
}

void 
DetectDodge::step()
{
  geometry_msgs::Twist cmd;

  switch (state_)
  {
  case GOING_FORWARD:
    // cmd.linear.x = ...;
    // cmd.angular.z = ...;

    cmd.linear.x = 1;
    cmd.linear.z = 0;

    if (detect_object_)
    {
      detect_ts_ = ros::Time::now();
      state_ = GOING_BACK;
      ROS_INFO("GOING_FORWARD -> GOING_BACK");
    }
    break;

  case GOING_BACK:
    // cmd.linear.x = ...;
    // cmd.angular.z = ...;

    cmd.linear.x = -1; //camilo: no se si poner numeros negativos aqui funcionará para ir para atras
    cmd.linear.z = 0;

    if ((ros::Time::now() - detect_ts_).toSec() > BACKING_TIME )
    {
      turn_ts_ = ros::Time::now();
      state_ = TURNING;
      ROS_INFO("GOING_BACK -> TURNING");
    }
    break;

  case TURNING:
    // cmd.linear.x = ...;
    // cmd.angular.z = ...;

    cmd.linear.x = 0;
    cmd.angular.z = 30; //camilo: no se cuantos grados es esto, hay que comprobarlo con el simulador

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