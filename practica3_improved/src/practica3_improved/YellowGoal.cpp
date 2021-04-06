#include "practica3_improved/YellowGoal.hpp"

namespace practica3
{
YellowGoal::YellowGoal() : buffer_(), listener_(buffer_), objectDetector_(), goalDetector_()
{
  pub_vel_=  n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  
  tfSet = false; 
  found = false;
}

bool YellowGoal::isClose()
{
  return objectDetector_.hasCollided();
}

void 
YellowGoal::setTFs()
{
  geometry_msgs::TransformStamped odom2bf_msg;
  
  try {
    odom2bf_msg = buffer_.lookupTransform("odom","base_footprint", ros::Time(0)); // esta excepcion salta constantemente y no puedo crear la transformada.
  } catch (std::exception & e) {
    return;
  }
  
  tf2::Stamped<tf2::Transform> odom2bf;
  tf2::fromMsg(odom2bf_msg, odom2bf);

  tf2::Stamped<tf2::Transform> bf2Goal;

  bf2Goal.setOrigin(tf2::Vector3(1, 0, 0));
  bf2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform odom2Goal = odom2bf * bf2Goal;

  geometry_msgs::TransformStamped odom2Goal_msg;

  odom2Goal_msg.header.stamp = ros::Time::now();
  odom2Goal_msg.header.frame_id = "odom";
  odom2Goal_msg.child_frame_id = "Yellow_Goal";

  odom2Goal_msg.transform = tf2::toMsg(odom2Goal);

  broadcaster_.sendTransform(odom2Goal_msg);
}

int 
YellowGoal::turnTo_TF()
{
  geometry_msgs::Twist cmd;
  
  geometry_msgs::TransformStamped bf2Goal_2_msg;
  try {
    bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Yellow_Goal", ros::Time(0));
  } catch (std::exception & e) {
    return -1;
  }

  double angle = atan2(bf2Goal_2_msg.transform.translation.y,bf2Goal_2_msg.transform.translation.x);

  if (angle > -ANGLE_INTERVAL && angle < ANGLE_INTERVAL)
  {
    cmd.linear.x = 0;
    cmd.angular.z = 0;
    pub_vel_.publish(cmd);
    return 0;
  }
  else {
    cmd.linear.x = 0;
    if (angle < 0){ 
      cmd.angular.z = -TURN_SPEED;
    } else {
      cmd.angular.z =  TURN_SPEED;
    }
    pub_vel_.publish(cmd);
    return 1;
  }
}

void 
YellowGoal::turnTo_IM()
{
  if(!isActive()) return;

  geometry_msgs::Twist cmd;

  goalDetector_.findObjectColor(YELLOW_NUMBER);
  if (goalDetector_.getX(YELLOW_NUMBER) > CENTER_SCREEN_COORDS - ANGLE_COORDS && goalDetector_.getX(YELLOW_NUMBER) < CENTER_SCREEN_COORDS + ANGLE_COORDS) {
    cmd.angular.z = 0;
    found = true;
  }
  else if (goalDetector_.getX(YELLOW_NUMBER) > CENTER_SCREEN_COORDS + ANGLE_COORDS) {
    cmd.angular.z = -TURN_SPEED;
    found = false;
  }
  else {
    cmd.angular.z = TURN_SPEED;
    found = false;
  }

  cmd.linear.x = 0;
  pub_vel_.publish(cmd);
}

void 
YellowGoal::moveForward()
{
  if(!isActive()) return;

  geometry_msgs::Twist cmd;
  cmd.linear.x = MOVEMENT_SPEED;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);
}

void
YellowGoal::stop()
{
  if (!isActive()) return;

  geometry_msgs::Twist cmd;
  cmd.linear.x = 0;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);
}

void
YellowGoal::step()
{
  if (!isActive()) {
    return;
  }
  
  if (!tfSet){
    turnTo_IM();
    if (found){
      if (isClose()) {
        setTFs();
        tfSet = true;
        stop();
      } else{
        moveForward();
      }
    }  
  } 
  else {
    if (turnTo_TF() == 0) {
      turnTo_IM();
      if (found) {
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