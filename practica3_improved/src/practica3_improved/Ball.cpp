#include "practica3_improved/Ball.hpp"

namespace practica3
{

Ball::Ball(): objectDetector_(), ballDetector_(), buffer_(), listener_(buffer_)
{
  pub_vel_=  n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  
  tfSet = false; 
  found = false;
}

bool Ball::isClose()
{  
  return ballDetector_.getBallY() > BALL_DETECTABLE_HEIGHT;
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

  tf2::Stamped<tf2::Transform> bf2Ball;

  bf2Ball.setOrigin(tf2::Vector3(1, 0, 0));
  bf2Ball.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform odom2Ball = bf2odom * bf2Ball;

  geometry_msgs::TransformStamped odom2Ball_msg;

  odom2Ball_msg.header.stamp = ros::Time::now();
  odom2Ball_msg.header.frame_id = "odom";
  odom2Ball_msg.child_frame_id = "Ball";

  odom2Ball_msg.transform = tf2::toMsg(odom2Ball);

  broadcaster_.sendTransform(odom2Ball_msg);

  
}

int 
Ball::turnTo_IM()
{
  if(!isActive()) return -1;
  geometry_msgs::Twist cmd;
  if (ballDetector_.getBallX() > CENTER_SCREEN_COORDS - 20 && ballDetector_.getBallX() < CENTER_SCREEN_COORDS + 20)
  {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    pub_vel_.publish(cmd);
    return 0;
  }
  else {
    cmd.linear.x = 0;
    cmd.angular.z = TURN_SPEED;
    pub_vel_.publish(cmd);
    return 1;
  }
}

void 
Ball::move()
{
  if(!isActive()) return;

  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist cmd;
  cmd.linear.x = MOVEMENT_SPEED;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}

void
Ball::stop()
{
  if (!isActive()) return;
  geometry_msgs::Twist cmd;
  cmd.linear.x = 0;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}

void
Ball::step()
{
  if (!isActive()){
    return;
  }

  if (turnTo_IM() == 0){
    found = true;
  }
  if (found){
    move();
    
    if (isClose()){
      setTFs();
      tfSet = true;
      found = false;
      stop();
    }
  }  
}  


    
} //practica3