#ifndef PROYECTO_FINAL_APPROACHOBJECT_H
#define PROYECTO_FINAL_APPROACHOBJECT_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string>

#include "sensor_msgs/LaserScan.h"

#include <tf/transform_listener.h>

#include <tf/transform_listener.h>
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

namespace proyecto_final
{

class ApproachObject : public BT::ActionNodeBase
{
  public:
    explicit ApproachObject(const std::string& name, const BT::NodeConfiguration & config);

    void halt();

    void move();

    //void laser_callback(const sensor_msgs::LaserScan::ConstPtr msg);
    void checkDistance();

    BT::NodeStatus tick();

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("object")};
    }

  private:
    bool reached_object;
    double object_x_;
    double object_y_;
    double robot_x_;
    double robot_y_;

    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;
    ros::Subscriber laser_sub_;
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;

};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL_APPROACHOBJECT_H
