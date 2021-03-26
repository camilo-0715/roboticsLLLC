#include "practica3/ball_operator.hpp"

namespace practica3 {

    Ball::Ball()
    {
      pub_vel_= n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
      ObjectDetector odt;
    }

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
      ROS_INFO("BALL FORWARD");

      geometry_msgs::Twist cmd;
      //hacemos que el robot avance hacía delante
      cmd.linear.x = movementSpeed;
      cmd.linear.z = 0;
      cmd.angular.z = 0;
      if (hasCollided())
        cmd.linear.x = 0;
      pub_vel_.publish(cmd);
      return;
    }
    bool
    Ball::hasCollided()
    {
      return odt.hasCollided();
    }
}