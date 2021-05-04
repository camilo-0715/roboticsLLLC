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

#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types_conversion.h>
#include <pcl_ros/transforms.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <std_msgs/Float32.h>
#include <sensor_msgs/PointCloud2.h>

namespace proyecto_final
{
  class Recognizer
  {
    public:
      Recognizer(std::string item);
      // method to check if a determinated item exists. returns bool
       
      void checkForObjectsResultCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg); 
      void cloudCB(const sensor_msgs::PointCloud2::ConstPtr& cloud_in);
      void setCenterObj(const int xmin, const int xmax, const int ymin, const int ymax );
      void init();

    private:
      ros::NodeHandle nh_;
      ros::Subscriber obj_sub_;
      ros::Subscriber cloud_sub_;
      
      std::string item;

      int num_classes;
      double object_prob = 0.0;
      std::string object_class = ""; 

      int center_w_object_ = 1; // Centro de los objetos
      int center_h_object_ = 1;
      double distances_[3]; 

      tf::TransformListener tfListener_;

      bool found = false;
  };
} // namespace proyecto_final

#endif // PROYECTO_FINAL__DN_RECOGNIZING_HPP__ 
