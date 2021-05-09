#ifndef PROYECTO_FINAL__APPROACHROOM_HPP
#define PROYECTO_FINAL__APPROACHROOM_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace proyecto_final
{

class ApproachRoom : public BT::ActionNodeBase
{
  public:
    explicit ApproachRoom(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__APPROACHROOM_HPP
