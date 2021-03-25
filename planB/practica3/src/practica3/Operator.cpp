#include "practica3/Operator.hpp"
#include "practica3/LaserDetector.hpp"
#include "practica3/Detector.hpp"

namespace practica3 {

    Operator::Operator()
    {
      pub_vel_= n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
    }
        

    int 
    Operator::turnTo(int obj)
    {
      geometry_msgs::Twist cmd;
      obj_color.setObj(obj);
      if (obj_color.getX() > CENTER_SCREEN_COORDS - 20 && obj_color.getX() < CENTER_SCREEN_COORDS + 20) // a ojo
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
    Operator::step(int obj)
    {
      // Depuración luego se quita
      ROS_INFO("[%s]", ros::this_node::getName().c_str());

      geometry_msgs::Twist cmd;
      if (obj == 1){  //Cuando sea la bola, detectarlo con las coordenadas
        obj_color.setObj(obj);
        if(obj_color.getY() > 460){
          std::cerr << "BOLA ENCONTRADA" << std::endl;  //BORRAR
          return;
        }
      }
      else{  //Detectar con laser
        if(obj_laser.isObject()){
          std::cerr << "PORTERÍA ENCONTRADA" << std::endl;  //BORRAR
          return;
        }
      }

      cmd.linear.x = movementSpeed;
      cmd.angular.z = 0;
      cmd.linear.z = 0;
      pub_vel_.publish(cmd);

      return;
    }
}