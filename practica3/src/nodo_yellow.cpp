#include <ctime>
#include "geometry_msgs/Twist.h"
#include <ros/ros.h>
#include <bica/Component.h>
#include "practica3/yellowGoal_detector.hpp"

class YellowGoal: public bica::Component
{
public:
  YellowGoal()
  {
    pub_vel_=  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  }
  
  ~YellowGoal()
  {
  }
  
  /************************************************
  void setTFs(valores obtenidos de los detectores)
  {
    establece los valores de las TFs
  }
  **************************************************/

  void turnTo()
  {
    if(!isActive()) return;

    geometry_msgs::Twist cmd;
    practica3::yellowGoal_detector bdt;

    cmd.linear.x = 0;
    cmd.angular.z = 0.5;
    pub_vel_.publish(cmd);

    while(true)
    {
      //en este if hay que poner que cuando detecte la pelota se meta en el if para que deje de
      //girar nose si esta bien porque no entendi muy bien ball detector
      //cuando baje del avion le pregunto a luismigei
      if(bdt.getYGoalY() == 2 && bdt.getYGoalX() == 2 )
      {
        break;
      }
    }


  }


  void step()
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

private:
  /***************
  Las trasformadas
  ****************/

  ros::NodeHandle n;
  ros::Publisher pub_vel_;

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node_B");  

  YellowGoal goal;  
  /***********************************************************
  Aqui se podria llamar a los detectores y despues a 
  un metodo que se llame setTFs() por ejemplo que haga guarde
  las trasformada en variables private
  ************************************************************/

  ros::Rate loop_rate(7);

  while(goal.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo haga el giro la 
    primera vez que se reactive 
    if (el estado anterio == !isActive()) {turnTo}
    ***********************************************************/ 

  	goal.step();

  	ros::spinOnce();

  	loop_rate.sleep();
  }  

  return 0;
}
