#ifndef PROYECTO_FINAL_APPROACHOBJECT_H
#define PROYECTO_FINAL_APPROACHOBJECT_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace proyecto_final
{

class ApproachObject : public BT::ActionNodeBase
{
  public:
    explicit ApproachObject(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
};

}  // namespace proyecto_final

#endif  // PROYECTO_FINAL_APPROACHOBJECT_H
