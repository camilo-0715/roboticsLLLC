#include "practica3/Ball.hpp"
#include "practica3/ball_detector.hpp"

#include "bica/Component.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include <ctime>

namespace practica3
{

Ball::Ball()
{
  //pub_vel_=  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
}

/************************************************
void setCoord(valores obtenidos de los detectores)
{
  establece los valores de las TFs
}
**************************************************/


void 
Ball::turnTo()
{
  /*
  if(!isActive()) return;

  geometry_msgs::Twist cmd;
  practica3::ball_detector bdt;

  cmd.linear.x = 0;
  cmd.angular.z = 0.5;
  pub_vel_.publish(cmd);

  while(true)
  {
    //en este if hay que poner que cuando detecte la pelota se meta en el if para que deje de
    //girar nose si esta bien porque no entendi muy bien ball detector
    //cuando baje del avion le pregunto a luismigei
    if(bdt.getBallY() == 2 && bdt.getBallX() == 2 )
    {
      break;
    }
  }

*/
}

void 
Ball::step()
{
  if(!isActive()) return;

  // Depuración luego se quita
  ROS_INFO("[%s]", ros::this_node::getName().c_str());

  /*geometry_msgs::Twist cmd;
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
  }*/

}
    
} //practica3