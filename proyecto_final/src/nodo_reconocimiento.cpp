#include "proyecto_final/dn_recognizing.hpp"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "reconizer");

  if (argc != 3) {
    ROS_INFO("EXPECTED ARGUMENTS -> PLACE OBJECT");
  } 
  else {
    proyecto_final::Recognizer reconizer(argv[2]);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
      reconizer.init();
      ros::spinOnce();
      loop_rate.sleep();
    }
  }  

  return 0;
}
