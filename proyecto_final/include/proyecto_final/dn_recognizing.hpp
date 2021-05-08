#ifndef PROYECTO_FINAL__DN_RECOGNIZING_HPP__
#define PROYECTO_FINAL__DN_RECOGNIZING_HPP__

#include "ros/ros.h"
#include <iostream>
#include <map>
#include "std_msgs/String.h"

#include <darknet_ros_msgs/BoundingBoxes.h>
#include <actionlib/client/simple_action_client.h>

#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types_conversion.h>
#include <pcl_ros/transforms.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "tf2/convert.h"

#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <std_msgs/Float32.h>
#include <sensor_msgs/PointCloud2.h>

namespace proyecto_final
{
  class Recognizer
  {
    public:
      Recognizer(std::string item);
       
      void darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg); 
      void cloudCB(const sensor_msgs::PointCloud2::ConstPtr& cloud_in);
      void setCenterObj(const int xmin, const int xmax, const int ymin, const int ymax );
      void setTFs(const double distance_x, const double distance_y, const double distance_z);
      void init();

    private:
      ros::NodeHandle nh_;
      ros::Subscriber obj_sub_;
      ros::Subscriber cloud_sub_;
      
      tf2_ros::Buffer buffer_;
      //tf2_ros::TransformListener listener_;
      tf2_ros::StaticTransformBroadcaster broadcaster_;

      std::string item;

      int num_classes;
      double object_prob = 0.0;
      std::string object_class = ""; 

      int center_w_object_ = -1; // Centro de los objetos
      int center_h_object_ = -1; 

      tf::TransformListener tfListener_;
      sensor_msgs::PointCloud2 cloud_out_;

      bool found = false;
  };
} // namespace proyecto_final

#endif // PROYECTO_FINAL__DN_RECOGNIZING_HPP__ 
