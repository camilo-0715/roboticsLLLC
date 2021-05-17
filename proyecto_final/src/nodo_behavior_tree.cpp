#include "proyecto_final/ApproachObject.hpp"
#include "proyecto_final/setTF.hpp"
#include "proyecto_final/ApproachRoom.hpp"
#include "proyecto_final/inRoom.hpp"
#include "proyecto_final/turnToTf.hpp"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "proyecto_final");
  ros::NodeHandle n;

  if (argc != 3) {
    ROS_INFO("EXPECTED ARGUMENTS -> PLACE OBJECT");
  } 

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<proyecto_final::ApproachObject>("ApproachObject"); // declare nodes
  factory.registerNodeType<proyecto_final::setTF>("setTF");
  factory.registerNodeType<proyecto_final::ApproachRoom>("ApproachRoom");
  factory.registerNodeType<proyecto_final::inRoom>("inRoom");
  factory.registerNodeType<proyecto_final::turnToTf>("turnToTf");

  auto blackboard = BT::Blackboard::create(); // set ports
  std::string roomInputted = argv[1];
  std::string objectInputted = argv[2];
  blackboard->set("object", objectInputted);
  blackboard->set("room", roomInputted);

  std::string pkgpath = ros::package::getPath("proyecto_final");
  std::string xml_file = pkgpath + "/proyecto_final_BT.xml";
   
  BT::Tree tree = factory.createTreeFromFile(xml_file, blackboard); // create tree with nodes and trees.
  ros::Rate loop_rate(5);

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.rootNode()->executeTick() == BT::NodeStatus::SUCCESS;

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
