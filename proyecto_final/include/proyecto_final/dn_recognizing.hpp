#ifndef PROYECTO_FINAL__DN_RECOGNIZING_HPP__
#define PROYECTO_FINAL__DN_RECOGNIZING_HPP__

#include "ros/ros.h"
#include <iostream>
#include <map>
#include "std_msgs/String.h"

// darknet_ros_msgs
#include <darknet_ros_msgs/CheckForObjectsAction.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <actionlib/client/simple_action_client.h>

namespace proyecto_final
{
  class Recognizer
  {
    public:
      Recognizer(std::string item);
      // method to check if a determinated item exists. returns bool
       
      void checkForObjectsResultCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg); 
      void init();

    private:
      ros::NodeHandle nh_;
      ros::Subscriber obj_sub_;

      std::string item;

      int num_classes;
      double object_prob = 0.0;
      std::string object_class = ""; 

      bool found = false;
  };
} // namespace proyecto_final

#endif // PROYECTO_FINAL__DN_RECOGNIZING_HPP__ 
