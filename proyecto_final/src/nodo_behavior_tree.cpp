#include "proyecto_final/ApproachObject.hpp"
#include "proyecto_final/TurnTo.hpp"
#include "proyecto_final/ApproachRoom.hpp"
#include "proyecto_final/inRoom.hpp"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "proyecto_final");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<proyecto_final::ApproachObject>("ApproachObject");
  factory.registerNodeType<proyecto_final::TurnTo>("TurnTo");
  factory.registerNodeType<proyecto_final::ApproachRoom>("ApproachRoom");
  factory.registerNodeType<proyecto_final::inRoom>("inRoom");

  std::string pkgpath = ros::package::getPath("proyecto_final");
  std::string xml_file = pkgpath + "/proyecto_final_BT.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  int count = 0;

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.rootNode()->executeTick() == BT::NodeStatus::SUCCESS;

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
