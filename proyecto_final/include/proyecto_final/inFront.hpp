#ifndef PROYECTO_FINAL__INFRONT_HPP
#define PROYECTO_FINAL__INFRONT_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string>

#include <tf/transform_listener.h>
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2/LinearMath/Transform.h"
#include "tf2/convert.h"

#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <std_msgs/Float32.h>

namespace proyecto_final
{

class inFront : public BT::ActionNodeBase
{
  public:
    explicit inFront(const std::string& name, const BT::NodeConfiguration & config);
  
    void halt();

    int turnTo_TF();


    BT::NodeStatus tick();
    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("object")};
    }

  private:
  
    ros::NodeHandle nh_;
    ros::Publisher pub_vel_;
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;

    const float ANGLE_INTERVAL = 0.05;
    const float TURN_SPEED = 0.27;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__INFRONT_HPP
