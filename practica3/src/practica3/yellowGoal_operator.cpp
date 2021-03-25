#include "practica3/yellowGoal_operator.hpp"

namespace practica3 {

    YellowGoal::YellowGoal()
    {
      ObjectDetector odt;
      pub_vel_= n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
    }
        
    void
    YellowGoal::setTF(){
      tf2_ros::Buffer buffer_;
      tf2_ros::TransformListener listener_(buffer_);
      tf2_ros::StaticTransformBroadcaster broadcaster;
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
      bf2Goal_msg.header.frame_id = "odom";
      bf2Goal_msg.child_frame_id = "Yellow_Goal";

      bf2Goal_msg.transform = tf2::toMsg(bf2Goal);

      broadcaster.sendTransform(bf2Goal_msg);

      geometry_msgs::TransformStamped bf2Goal_2_msg;

      try{
        bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Yellow_Goal", ros::Time(0));
      } catch (std::exception & e){
        return;
      }
    }

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
      if (hasCollided())
        cmd.linear.x = 0;
      pub_vel_.publish(cmd);

      return;
    }
    bool
    YellowGoal::hasCollided()
    {
      return odt.hasCollided();
    }
}