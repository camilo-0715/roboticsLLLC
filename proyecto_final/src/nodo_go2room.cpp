#include "proyecto_final/ApproachObject.hpp"
#include "proyecto_final/look4object.hpp"
#include "proyecto_final/ApproachRoom.hpp"
#include "proyecto_final/inRoom.hpp"
#include "proyecto_final/inFront.hpp"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "parte_primera");
  ros::NodeHandle n;

  if (argc != 3) {
    ROS_INFO("EXPECTED ARGUMENTS -> PLACE OBJECT");
  } 

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<proyecto_final::ApproachRoom>("ApproachRoom");
  factory.registerNodeType<proyecto_final::InRoom>("InRoom");

  auto blackboard = BT::Blackboard::create(); 
  std::string roomInputted = argv[1];
  std::string objectInputted = argv[2];
  blackboard->set("room", roomInputted);

  std::string pkgpath = ros::package::getPath("proyecto_final");
  std::string xml_file = pkgpath + "/room_BT.xml";
   
  BT::Tree tree = factory.createTreeFromFile(xml_file, blackboard);
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
