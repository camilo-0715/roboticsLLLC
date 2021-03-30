#include "practica3_improved/BlueGoal.hpp"

namespace practica3
{
BlueGoal::BlueGoal()  : buffer_(), listener_(buffer_), objectDetector_(), goalDetector_()
{
  pub_vel_=  n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  bool first_search = true;
  bool previous_state = false; 
  bool found = false;
  
}

bool BlueGoal::isClose()
{
  return objectDetector_.hasCollided();
}

void BlueGoal::setTFs()
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
  odom2Goal_msg.child_frame_id = "Blue_Goal";

  odom2Goal_msg.transform = tf2::toMsg(odom2Goal);

  broadcaster_.sendTransform(odom2Goal_msg);

  try{
    bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Yellow_Goal", ros::Time(0));
  } catch (std::exception & e){
    return;
  }

}

int 
BlueGoal::turnTo_TF()
{
  geometry_msgs::Twist cmd;
  double angle = atan2(bf2Goal_2_msg.transform.translation.y,bf2Goal_2_msg.transform.translation.x);
  std::cout << angle << std:: endl;
  if (angle > -0.05 && angle < 0.05)
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

int 
BlueGoal::turnTo_IM()
{
  if(!isActive()) return -1;
  geometry_msgs::Twist cmd;
  if (goalDetector_.getBGoalX() > CENTER_SCREEN_COORDS - 20 && goalDetector_.getBGoalX() < CENTER_SCREEN_COORDS + 20)
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
BlueGoal::move()
{
  if(!isActive()) return;

  // Depuración luego se quita
  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist cmd;
  cmd.linear.x = MOVEMENT_SPEED;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}

void
BlueGoal::stop()
{
  if (!isActive()) return;
  geometry_msgs::Twist cmd;
  cmd.linear.x = 0;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

}

void
BlueGoal::step()
{
  if (!isActive()){
    return;
  }

  if (!previous_state){
    ROS_INFO("***********************************************************");
    found = false;
  }

  if (!tfSet){
    if (turnTo_IM() == 0){
      found = true;
    }
    if (found){
      move();
      ROS_INFO("..................................");
      if (isClose()){
        setTFs();
        tfSet = true;
        stop();
      }
    }
  }
  else{
    if (turnTo_TF() == 0){
        ROS_INFO("TF turn");
        move();
        if (isClose()){ 
         stop();
        }
    }  
  }

  previous_state = isActive();  
}
    
} //practica3