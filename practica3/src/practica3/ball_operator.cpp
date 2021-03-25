#include "practica3/ball_operator.hpp"

namespace practica3 {

    Ball::Ball()
    {
      pub_vel_= n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
    }
        
    /************************************************
    void setCoord(valores obtenidos de los detectores)
    {
      establece los valores de las TFs
    }
    **************************************************/


    int 
    Ball::turnTo(ball_detector bdt)
    {
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

      // Depuración luego se quita
      ROS_INFO("[%s]", ros::this_node::getName().c_str());

      geometry_msgs::Twist cmd;
      //hacemos que el robot avance hacía delante
      cmd.linear.x = movementSpeed;
      cmd.linear.z = 0;
      cmd.angular.z = 0;
      pub_vel_.publish(cmd);
      return;
    }
}