#ifndef PROYECTO_FINAL__INROOM_HPP
#define PROYECTO_FINAL__INROOM_HPP

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace proyecto_final
{

class inRoom : public BT::ActionNodeBase
{
  public:
    explicit inRoom(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL__INROOM_HPP
