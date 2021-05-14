#ifndef PROYECTO_FINAL__INROOM_HPP
#define PROYECTO_FINAL__INROOM_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include "proyecto_final/coordsFile.hpp"
#include <string>

#include <tf/transform_listener.h>
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#include <move_base_msgs/MoveBaseAction.h>


namespace proyecto_final
{

class InRoom : public BT::ActionNodeBase
{
  public:
    explicit InRoom(const std::string& name, const BT::NodeConfiguration& config);
    void setTargetCoords(std::string destination);
    bool isInRoom();
    void halt();
    void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);
    BT::NodeStatus tick();
    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("room")};
    }

  private:
    ros::NodeHandle nh_;
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;

    ros::Subscriber movebase_sub_;

    double actual_x_ = 0;
    double actual_y_ = 0;
    double target_x_;
    double target_y_;

    double bedroom_x = coordsData::point1_x; // coords are in coordsfile.hpp
    double bedroom_y = coordsData::point1_y;

    double empty_room_x = coordsData::point2_x;
    double empty_room_y = coordsData::point2_y;

    double gym_x = coordsData::point3_x;
    double gym_y = coordsData::point3_y;

    double kitchen_x = coordsData::point4_x;
    double kitchen_y = coordsData::point4_y;
  
  };

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__INROOM_HPP
