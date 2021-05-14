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

#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{

class InFront : public BT::ActionNodeBase
{
  public:
    explicit InFront(const std::string& name, const BT::NodeConfiguration & config);
    bool isInFront();
    void halt();
    void darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg);

    BT::NodeStatus tick();
    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("object")};
    }

  private:
  
    ros::NodeHandle nh_;
    ros::Subscriber obj_sub_;

    bool found = false;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__INFRONT_HPP
