#include "practica3/BlueGoal.hpp"

namespace practica3
{
BlueGoal::BlueGoal()  : buffer_(), listener_(buffer_)
{
  pub_vel_=  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

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

  tf2::Stamped<tf2::Transform> odom2Goal;

  odom2Goal.setOrigin(tf2::Vector3(0, 0, 0));
  odom2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

  tf2::Transform bf2Goal = bf2odom * odom2Goal;

  geometry_msgs::TransformStamped bf2Goal_msg;

  bf2Goal_msg.header.stamp = ros::Time::now();
  bf2Goal_msg.header.frame_id = "base_footprint";
  bf2Goal_msg.child_frame_id = "Blue_Goal";

  bf2Goal_msg.transform = tf2::toMsg(bf2Goal);

  broadcaster.sendTransform(bf2Goal_msg);

  geometry_msgs::TransformStamped bf2Goal_2_msg;

  try{
    bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Blue_Goal", ros::Time(0));
  } catch (std::exception & e){
    return;
  }

}

void 
BlueGoal::turnTo()
{
  if(!isActive()) return;

  geometry_msgs::Twist cmd;
  practica3::blueGoal_detector bdt;

  cmd.linear.x = 0;
  cmd.angular.z = 0.5;
  pub_vel_.publish(cmd);

  while(true)
  {
    //en este if hay que poner que cuando detecte la pelota se meta en el if para que deje de
    //girar nose si esta bien porque no entendi muy bien ball detector
    //cuando baje del avion le pregunto a luismigei
    if(bdt.getBGoalY() == 2 && bdt.getBGoalX() == 2 )
    {
      break;
    }
  }


}

void 
BlueGoal::step()
{
  if(!isActive()) return;

  // Depuración luego se quita
  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  geometry_msgs::Twist cmd;
  //hacemos que el robot avance hacía delante
  ros::Time init_time_ = ros::Time::now();
  cmd.linear.x = 0.5;
  cmd.linear.z = 0;
  cmd.angular.z = 0;
  pub_vel_.publish(cmd);

  //cuanto haya pasado el tiempo definido en la variable advance_time paramos el robot
  const double advance_time = 0.5;
  while(true)
  {
  ros::Time actual_time_ = ros::Time::now();
    if (actual_time_.toSec() >= advance_time)
    {
      break;
    }
  }

}
    
} //practica3