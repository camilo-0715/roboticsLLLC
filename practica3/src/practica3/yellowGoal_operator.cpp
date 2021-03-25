#include "practica3/yellowGoal_operator.hpp"

namespace practica3 {

    YellowGoal::YellowGoal()
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
    YellowGoal::turnTo(yellowGoal_detector ygdt)
    {
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
      // Depuración luego se quita
      ROS_INFO("[%s]", ros::this_node::getName().c_str());

      geometry_msgs::Twist cmd;

      cmd.linear.x = movementSpeed;
      cmd.angular.z = 0;
      cmd.linear.z = 0;
      pub_vel_.publish(cmd);

      return;
    }
}