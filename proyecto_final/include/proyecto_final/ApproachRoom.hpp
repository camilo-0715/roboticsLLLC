#ifndef PROYECTO_FINAL__APPROACHROOM_HPP
#define PROYECTO_FINAL__APPROACHROOM_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include <string>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "proyecto_final/coordsFile.hpp"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace proyecto_final
{
class ApproachRoom : public BT::ActionNodeBase
{
  public:
    explicit ApproachRoom(const std::string& name, const BT::NodeConfiguration & config);

    void halt();
    //void init( const std::string& room);
    BT::NodeStatus tick();
    static BT::PortsList providedPorts() // had to implemet this to use ports.
    {
      return { BT::InputPort<std::string>("room")};
    }


  private:

    ros::NodeHandle nh_;
    bool arrived, sent;
    move_base_msgs::MoveBaseGoal goal;
    //we create a MoveBaseClient type object named ac so we can send the new coords to move the robot further on
    MoveBaseClient ac;

    void setTargetCoords(std::string destination);
    void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result);
    void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);
    void moveRobot(double x, double y, double orientation);

    double actual_x_;
    double actual_y_;
    double target_x_;
    double target_y_;

    double bedroom_x = coordsData::point1_x; // check coordsFile.hpp for data. did this to modify it quicker when doing it presentially.
    double bedroom_y = coordsData::point1_y;

    double empty_room_x = coordsData::point2_x;
    double empty_room_y = coordsData::point2_y;

    double gym_x = coordsData::point3_x;
    double gym_y = coordsData::point3_y;

    double kitchen_x = coordsData::point4_x;
    double kitchen_y = coordsData::point4_y;
  
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__APPROACHROOM_HPP
