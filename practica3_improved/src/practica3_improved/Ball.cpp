#include "practica3_improved/Ball.hpp"

namespace practica3
{

Ball::Ball(): objectDetector_(), ballDetector_(), buffer_(), listener_(buffer_)
{
  pub_vel_=  n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  bool first_search = true;
  bool previous_state = false; 
  bool found = false;
}

bool Ball::isClose()
{
  std::cout << ballDetector_.getBallY() << std::endl;
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

  tf2::Stamped<tf2::Transform> odom2Goal;

  odom2Goal.setOrigin(tf2::Vector3(0, 0, 0));
  odom2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform bf2Goal = bf2odom * odom2Goal;

  geometry_msgs::TransformStamped bf2Ball_msg;

  bf2Ball_msg.header.stamp = ros::Time::now();
  bf2Ball_msg.header.frame_id = "base_footprint";
  bf2Ball_msg.child_frame_id = "Ball";

  bf2Ball_msg.transform = tf2::toMsg(bf2Goal);

  broadcaster_.sendTransform(bf2Ball_msg);

  try{
    bf2Ball_2_msg = buffer_.lookupTransform("base_footprint", "Ball", ros::Time(0));
  } catch (std::exception & e){
    return;
  }
}

int 
Ball::turnTo_TF()
{
  geometry_msgs::Twist cmd;
  double angle = atan2(bf2Ball_2_msg.transform.translation.y,bf2Ball_2_msg.transform.translation.x);
  
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
    ROS_INFO("NA");
    return;
  }
  if (!previous_state){
      ROS_INFO("***********************************************************");
      found = false;
    }
  if (turnTo_IM() == 0){
    found = true;
  }

  if (!found){
    if (first_search){
      ROS_INFO("--------------------------------------------------------------------------");
      first_search = false;
    } else if (!first_search){ //añadir ... && goal.turnTo_TF()) ...
      //found = true;
      ROS_INFO("It's the second search");
    }
  }

  else {
    move();
    ROS_INFO("..................................");
    if (isClose()){
      ROS_INFO("It should be making the TFs");
      setTFs();
      stop();
    }
  }   
  previous_state = isActive();  

}
    
} //practica3