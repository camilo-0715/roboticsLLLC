#include "practica3_improved/Ball.hpp"

namespace practica3
{

Ball::Ball(): objectDetector_(), ballDetector_(), buffer_(), listener_(buffer_)
{
  pub_vel_=  n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  
  tfSet = false; 
  found = false;
}

bool 
Ball::isClose()
{  
  return ballDetector_.getY(BALL_NUMBER) > BALL_DETECTABLE_HEIGHT;
}

void 
Ball::setTFs()
{
  geometry_msgs::TransformStamped odom2bf_msg;
  
  try {
    odom2bf_msg = buffer_.lookupTransform("odom","base_footprint", ros::Time(0)); // esta excepcion salta constantemente y no puedo crear la transformada.
  } catch (std::exception & e) {
    return;
  }
  
  tf2::Stamped<tf2::Transform> odom2bf;
  tf2::fromMsg(odom2bf_msg, odom2bf);

  tf2::Stamped<tf2::Transform> bf2Ball;

  bf2Ball.setOrigin(tf2::Vector3(1, 0, 0));
  bf2Ball.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform odom2Ball = odom2bf * bf2Ball;

  geometry_msgs::TransformStamped odom2Ball_msg;

  odom2Ball_msg.header.stamp = ros::Time::now();
  odom2Ball_msg.header.frame_id = "odom";
  odom2Ball_msg.child_frame_id = "Ball";

  odom2Ball_msg.transform = tf2::toMsg(odom2Ball);

  broadcaster_.sendTransform(odom2Ball_msg);
}

int 
Ball::turnTo_TF()
{
  geometry_msgs::Twist cmd;

  geometry_msgs::TransformStamped bf2Ball_2_msg;
  try {
    bf2Ball_2_msg = buffer_.lookupTransform("base_footprint", "Ball", ros::Time(0));
  } catch (std::exception & e) {
    return -1;
  }

  double angle = atan2(bf2Ball_2_msg.transform.translation.y,bf2Ball_2_msg.transform.translation.x);

  if (angle > -ANGLE_INTERVAL && angle < ANGLE_INTERVAL) {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    pub_vel_.publish(cmd);
    return 0;
  }
  else {
    cmd.linear.x = 0;
    if (angle < 0) {
      cmd.angular.z = -TURN_SPEED;
    } else {
      cmd.angular.z = TURN_SPEED;
    }
    pub_vel_.publish(cmd);
    return 1;
  }
}

void
Ball::turnTo_IM()
{

  if(!isActive()) return;
  geometry_msgs::Twist cmd;
  ballDetector_.findObjectColor(BALL_NUMBER);
  if (ballDetector_.getX(BALL_NUMBER) >= CENTER_SCREEN_COORDS - ANGLE_COORDS && ballDetector_.getX(BALL_NUMBER) <= CENTER_SCREEN_COORDS + ANGLE_COORDS) {
    cmd.angular.z = 0;
    found = true;
  }
  else if (ballDetector_.getX(BALL_NUMBER) < CENTER_SCREEN_COORDS - ANGLE_COORDS) {
    cmd.angular.z = TURN_SPEED;
    found = false;
  }
  else {
    cmd.angular.z = -TURN_SPEED;
    found = false;
  }

  cmd.linear.x = 0;
  pub_vel_.publish(cmd);
}

void 
Ball::moveForward()
{
  if(!isActive()) return;

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

  if (!tfSet) {
    turnTo_IM();
    if (found) {
      if (isClose()) {
        setTFs();
        tfSet = true;
        stop();
      } else {
        moveForward();
      }
    }  
  } 
  else {
    if (turnTo_TF() == 0) {
      turnTo_IM();
      if (found){
        if (isClose()) {
          stop();
        } else {
          moveForward();
        }
      } else {
        tfSet = false;
      }
    }
  }
}  

} // namespace practica3