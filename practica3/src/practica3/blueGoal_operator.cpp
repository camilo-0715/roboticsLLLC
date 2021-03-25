#include "practica3/blueGoal_operator.hpp"

namespace practica3 {

    BlueGoal::BlueGoal()
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
    BlueGoal::turnTo(blueGoal_detector bgdt)
    {
      geometry_msgs::Twist cmd;
      if (bgdt.getBGoalX() > CENTER_SCREEN_COORDS - 20 && bgdt.getBGoalX() < CENTER_SCREEN_COORDS + 20) // a ojo
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
    BlueGoal::step()
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