#ifndef PROYECTO_FINAL__TURN_TO_HPP
#define PROYECTO_FINAL__TURN_TO_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace proyecto_final
{

class TurnTo : public BT::ActionNodeBase
{
  public:
    explicit TurnTo(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__TURN_TO_HPP
