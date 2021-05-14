#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{
  Recognizer::Recognizer(std::string item_in) : item(item_in), tfListener_()
  {
    std::cout << "\n[DN RECOGNIZING] constructor \n" << std::endl;
    tfSet = false;
    obj_sub_ = nh_.subscribe("/darknet_ros/bounding_boxes", 1, &Recognizer::darknetCB, this);
    cloud_sub_ = nh_.subscribe("/camera/depth/points", 1, &Recognizer::cloudCB, this);
  }
  
  void 
  Recognizer::darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
  {
    int i = 0;
    std::cout << "\n[DN RECOGNIZING] darknet \n" << std::endl;  // Depuracion <- BORRAR
    found = false;
    num_classes = msg->bounding_boxes.size();

    while (i < num_classes && !found) {
      if (msg->bounding_boxes[i].Class == item && msg->bounding_boxes[i].probability > 0.5) {
        found = true;
        setCenterObj(msg->bounding_boxes[i].xmin, msg->bounding_boxes[i].xmax, msg->bounding_boxes[i].ymin, msg->bounding_boxes[i].ymax);

        //  ----------  CLOUD
        std::cout << "\n[DN RECOGNIZING] cloud\n" << std::endl;   // Depuracion <- BORRAR
        auto pcrgb = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
        pcl::fromROSMsg(cloud_, *pcrgb);
        auto point = pcrgb->at(center_w_object_, center_h_object_);
        ROS_INFO("[DN RECOGNIZING] X: %f, Y: %f\n", point.x, point.y); // Depuracion <- BORRAR

        //  ------------  TF
        std::cout << "[DN RECOGNIZING] set tf\n" << std::endl;   // Depuracion <- BORRAR
        if (isnan(point.x)||isnan(point.y)){
          std::cout << "[DN RECOGNIZING] isnan\n" << std::endl;   // Depuracion <- BORRAR
          return;
        }
        setTFs(point.x, point.y, point.z);
      }
      i++;
    } 
  }

  void 
  Recognizer::cloudCB(const sensor_msgs::PointCloud2::ConstPtr& cloud_in)
  {
    std::cout << "[DN RECOGNIZING] cloud 1 \n" << std::endl;   // Depuracion <- BORRAR

    try {
      pcl_ros::transformPointCloud("map", *cloud_in, cloud_, tfListener_);
    }
    catch(tf::TransformException & ex) {
      ROS_ERROR_STREAM("Transform error of sensor data: " << ex.what() << ", quitting callback");
      return;
    } 
  }

  void 
  Recognizer::setCenterObj(const int xmin, const int xmax, const int ymin, const int ymax )
  {
    center_w_object_ = xmin + (xmax - xmin) / 2;
    center_h_object_ = ymin + (ymax - ymin) / 2;

    std::cout << "[DN RECOGNIZING] w_center: " << center_w_object_ << std::endl; // Depuracion <- BORRAR
    std::cout << "[DN RECOGNIZING] h_center: " << center_h_object_ << std::endl; // Depuracion <- BORRAR
  }

  void 
  Recognizer::setTFs(const double distance_x, const double distance_y, const double distance_z)
  {
    geometry_msgs::TransformStamped transform_msg;
    transform_msg.header.stamp = ros::Time::now();
    transform_msg.header.frame_id = "map";
    transform_msg.child_frame_id = item;

    transform_msg.transform.translation.x = distance_x;
    transform_msg.transform.translation.y = distance_y;
    transform_msg.transform.translation.z = distance_z;

    transform_msg.transform.rotation.x = 0.0;
    transform_msg.transform.rotation.y = 0.0;
    transform_msg.transform.rotation.z = 0.0;
    transform_msg.transform.rotation.w = 1.0;
    
    broadcaster_.sendTransform(transform_msg);
    tfSet = true;
  }

  void 
  Recognizer::init() {
    if (found) {
      ROS_INFO("[DN RECOGNIZING] found");
    } else {
      ROS_INFO("[DN RECOGNIZING] not found");
    }
  }

  bool
  Recognizer::foundObj() {
    return found;
  }

} // namespace proyecto_final