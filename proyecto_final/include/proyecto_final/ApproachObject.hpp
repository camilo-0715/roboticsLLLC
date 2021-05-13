#ifndef PROYECTO_FINAL_APPROACHOBJECT_H
#define PROYECTO_FINAL_APPROACHOBJECT_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string>

#include "sensor_msgs/LaserScan.h"



namespace proyecto_final
{

class ApproachObject : public BT::ActionNodeBase
{
  public:
    explicit ApproachObject(const std::string& name, const BT::NodeConfiguration & config);

    void halt();

    void move();

    void laser_callback(const sensor_msgs::LaserScan::ConstPtr msg);

    BT::NodeStatus tick();

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("object")};
    }

  private:
    bool reached_object;

    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;
    ros::Subscriber laser_sub_;


};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL_APPROACHOBJECT_H
