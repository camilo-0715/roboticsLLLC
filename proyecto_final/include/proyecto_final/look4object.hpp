#ifndef PROYECTO_FINAL__TURN_TO_HPP
#define PROYECTO_FINAL__TURN_TO_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <darknet_ros_msgs/BoundingBoxes.h>
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

#include <string>

#include "proyecto_final/dn_recognizing.hpp"


namespace proyecto_final
{

class Look4object : public BT::ActionNodeBase
{
  public:
    explicit Look4object(const std::string& name, const BT::NodeConfiguration & config);

    void halt();
    void turn();
    void turnTo_TF();
    void darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg);
    BT::NodeStatus tick();

    static BT::PortsList providedPorts()
    {
      return { BT::InputPort<std::string>("object")};
    }

  private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;
    
    geometry_msgs::Twist cmd_;

    proyecto_final::Recognizer recognizer_; 
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;

    const float ANGLE_INTERVAL = 0.1;
    const float TURN_SPEED = 0.15;

    bool centered = false;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__TURN_TO_HPP
