#include "practica2/DetectDodge.h"

namespace practica2
{

DetectDodge::DetectDodge()
: state_(GOING_FORWARD), detect_object_left_(false), detect_object_right_(false), detect_object_center_(false)
{
  sub_laser_ = n.subscribe("/scan", 1, &DetectDodge::laserCallback, this); //camilo: estoy hay que cambiarlo para subscribirse al laser en vez de al buumper
  // pub_vel_ = n_.advertise<...>(...)
  pub_vel_ = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

}

void 
DetectDodge::laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  int rightObjectCounter = 0;
  int leftObjectCounter = 0;
  int centerObjectCounter = 0;

  for (int i = 0; i < msg->ranges.size(); i++) {
  
      if (msg->ranges[i] < OBSTACLE_DISTANCE) {
        rightObjectCounter++;
      }
      else if (i < (msg->ranges.size()/3)*2) {
      if (msg->ranges[i] < OBSTACLE_DISTANCE) {
        centerObjectCounter++;
      }
      else {
      if (msg->ranges[i] < OBSTACLE_DISTANCE) {
        leftObjectCounter++;
      }
    }
  }
  
  detect_object_left_ = (leftObjectCounter > (msg->ranges.size()/3)/2);
  detect_object_center_ = (centerObjectCounter > (msg->ranges.size()/3)/2);
  detect_object_right_ = (rightObjectCounter > (msg->ranges.size()/3)/2);

  if (detect_object_left_) {
    ROS_INFO("OBJECT LEFT");
  }
  if (detect_object_center_) {
    ROS_INFO("OBJECT CENTER");
  }
  if (detect_object_right_) {
    ROS_INFO("OBJECT RIGHT");
  }
}
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

    if (detect_object_right_ || detect_object_left_ || detect_object_center_) {
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

    if ((ros::Time::now() - detect_ts_).toSec() > BACKING_TIME ) {
      turn_ts_ = ros::Time::now();
      state_ = TURNING;
      ROS_INFO("GOING_BACK -> TURNING");
    }
    break;

  case TURNING:
    // cmd.linear.x = ...;
    // cmd.angular.z = ...;

    cmd.linear.x = 0;
    cmd.angular.z = 20; //camilo: no se cuantos grados es esto, hay que comprobarlo con el simulador

    if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME ) {
      state_ = GOING_FORWARD;
      ROS_INFO("TURNING -> GOING_FORWARD");
    }
    break;
  }

  pub_vel_.publish(cmd);
}
}
