#ifndef PROYECTO_FINAL_APPROACHOBJECT_H
#define PROYECTO_FINAL_APPROACHOBJECT_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"
#include <string>

namespace proyecto_final
{

class ApproachObject : public BT::ActionNodeBase
{
  public:
    explicit ApproachObject(const std::string& name, const BT::NodeConfiguration & config);

    void halt();

    BT::NodeStatus tick();

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("object")};
    }

  private:
    int counter_;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL_APPROACHOBJECT_H
