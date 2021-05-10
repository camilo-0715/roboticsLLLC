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

  if (argc != 3) {
    ROS_INFO("EXPECTED ARGUMENTS -> PLACE OBJECT");
  } 

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<proyecto_final::ApproachObject>("ApproachObject");
  factory.registerNodeType<proyecto_final::TurnTo>("TurnTo");
  factory.registerNodeType<proyecto_final::ApproachRoom>("ApproachRoom");
  factory.registerNodeType<proyecto_final::inRoom>("inRoom");

  std::string pkgpath = ros::package::getPath("proyecto_final");
  std::string xml_file = pkgpath + "/proyecto_final_BT.xml";

  /* puertos y Blackboard
  //Documentacion: https://www.behaviortree.dev/tutorial_02_basic_ports/

  auto blackboard = BT::Blackboard::create();
  blackboard->set("room", argv[1]);
  blackboard->set("object", argv[2]);
  */
   
  BT::Tree tree = factory.createTreeFromFile(xml_file);

  /*
  // Documentacion: https://www.behaviortree.dev/tutorial_08_additional_args/
 
  // itera a traves de todos los nodos y llama a init si 
  // hay un TurnTo o AproachRoom
  for( auto& node: tree.nodes )
  {
    if( auto ApproachRoom = dynamic_cast<ApproachRoom*>( node.get() ))
    {
      ApproachRoom->init(argv[1]);
    }
    if( auto TurnTo = dynamic_cast<TurnTo*>( node.get() ))
    {
      TurnTo->init(argv[2]);
    }
  }*/

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
