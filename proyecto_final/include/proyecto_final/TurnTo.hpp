#ifndef PROYECTO_FINAL__TURN_TO_HPP
#define PROYECTO_FINAL__TURN_TO_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

#include <string>

#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{

class TurnTo : public BT::ActionNodeBase
{
  public:
    explicit TurnTo(const std::string& name);

    void halt();
    //void init( const std::string& obj);
    void turn();
    void stop();
    BT::NodeStatus tick();

  private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;

    //std::string obj_;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__TURN_TO_HPP
