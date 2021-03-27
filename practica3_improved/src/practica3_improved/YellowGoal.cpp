#include "practica3_improved/YellowGoal.hpp"

namespace practica3
{
YellowGoal::YellowGoal() : buffer_(), listener_(buffer_), odt(), ygdt()
{
  pub_vel_=  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

}

bool YellowGoal::isClose()
{
  return odt.hasCollided();
}

void 
YellowGoal::setTFs()
{
  geometry_msgs::TransformStamped bf2odom_msg;
  
  try{
    bf2odom_msg = buffer_.lookupTransform("odom","base_footprint", ros::Time(0)); // esta excepcion salta constantemente y no puedo crear la transformada.
  } catch (std::exception & e){
    return;
  }
  
  tf2::Stamped<tf2::Transform> bf2odom;
  tf2::fromMsg(bf2odom_msg, bf2odom);

  tf2::Stamped<tf2::Transform> bf2Goal;

  bf2Goal.setOrigin(tf2::Vector3(1, 0, 0));
  bf2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform odom2Goal = bf2odom * bf2Goal;

  geometry_msgs::TransformStamped odom2Goal_msg;

  odom2Goal_msg.header.stamp = ros::Time::now();
  odom2Goal_msg.header.frame_id = "odom";
  odom2Goal_msg.child_frame_id = "Yellow_Goal";

  odom2Goal_msg.transform = tf2::toMsg(odom2Goal);

  broadcaster.sendTransform(odom2Goal_msg);

  try{
    bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Yellow_Goal", ros::Time(0));
  } catch (std::exception & e){
    return;
  }
}

/*
int 
YellowGoal::turnTo_TF()
{
  geometry_msgs::Twist cmd;
  double angle = atan2(bf2Goal_2_msg.transform.translation.y,bf2Goal_2_msg.transform.translation.x);
  
  if (angle > -0.05 && angle < 0.05)
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
*/

int 
YellowGoal::turnTo_IM()
{
  if(!isActive()) return -1;
  geometry_msgs::Twist cmd;
  if (ygdt.getYGoalX() > CENTER_SCREEN_COORDS - 20 && ygdt.getYGoalX() < CENTER_SCREEN_COORDS + 20)
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
YellowGoal::step()
{
  if(!isActive()) return;

  // Depuración luego se quita
  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist cmd;
  cmd.linear.x = movementSpeed;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}

} //practica3