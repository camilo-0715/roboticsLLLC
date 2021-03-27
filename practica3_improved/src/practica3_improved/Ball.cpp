#include "practica3_improved/Ball.hpp"
#include "practica3_improved/ball_detector.hpp"

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <ctime>

namespace practica3
{

Ball::Ball(): odt(), bdt(), buffer_(), listener_(buffer_)
{
  pub_vel_=  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

bool Ball::isClose()
{
  return odt.hasCollided();
}

void Ball::setTFs()
{
  geometry_msgs::TransformStamped bf2odom_msg;
  
  try{
    bf2odom_msg = buffer_.lookupTransform("odom","base_footprint", ros::Time(0)); // esta excepcion salta constantemente y no puedo crear la transformada.
  } catch (std::exception & e){
    return;
  }
  
  tf2::Stamped<tf2::Transform> bf2odom;
  tf2::fromMsg(bf2odom_msg, bf2odom);

  tf2::Stamped<tf2::Transform> odom2Goal;

  odom2Goal.setOrigin(tf2::Vector3(0, 0, 0));
  odom2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform bf2Goal = bf2odom * odom2Goal;

  geometry_msgs::TransformStamped bf2Ball_msg;

  bf2Ball_msg.header.stamp = ros::Time::now();
  bf2Ball_msg.header.frame_id = "base_footprint";
  bf2Ball_msg.child_frame_id = "Ball";

  bf2Ball_msg.transform = tf2::toMsg(bf2Goal);

  broadcaster.sendTransform(bf2Ball_msg);

  geometry_msgs::TransformStamped bf2Ball_2_msg;

  try{
    bf2Ball_2_msg = buffer_.lookupTransform("base_footprint", "Yellow_Goal", ros::Time(0));
  } catch (std::exception & e){
    return;
  }

}

int 
Ball::turnTo_IM()
{
  if(!isActive()) return -1;
  geometry_msgs::Twist cmd;
  if (bdt.getBallX() > CENTER_SCREEN_COORDS - 20 && bdt.getBallX() < CENTER_SCREEN_COORDS + 20)
  {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    pub_vel_.publish(cmd);
    return 0;
  }
  else {
    cmd.linear.x = 0;
    cmd.angular.z = turnSpeed;
    pub_vel_.publish(cmd);
    return 1;
  }
}

void 
Ball::step()
{
  if(!isActive()) return;

  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist cmd;
  cmd.linear.x = movementSpeed;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}
    
} //practica3