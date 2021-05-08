#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{
  Recognizer::Recognizer(std::string item_in) : item(item_in)
  {
    obj_sub_ = nh_.subscribe("/darknet_ros/bounding_boxes", 1, &Recognizer::darknetCB, this);
    cloud_sub_ = nh_.subscribe("/camera/depth/points", 1, &Recognizer::cloudCB, this);
  }

  void 
  Recognizer::darknetCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
  {
    int i = 0;
    found = false;

    std::cout << "\nDARKNET \n" << std::endl;  // Depuracion <- BORRAR

    num_classes = msg->bounding_boxes.size();

    // Hecho en un WHILE para que en el caso que haya varios objetos que cumplan la condición del if coja solo el primero
    // También se podría cambiar a un FOR  <- BORRAR
    while (i < num_classes && !found) {
      if (msg->bounding_boxes[i].Class == item && msg->bounding_boxes[i].probability > 0.5) {
        found = true;
        setCenterObj(msg->bounding_boxes[i].xmin, msg->bounding_boxes[i].xmax, msg->bounding_boxes[i].ymin, msg->bounding_boxes[i].ymax);

        std::cout << "\nCLOUD\n" << std::endl;   // Depuracion <- BORRAR

        auto pcrgb = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();

        std::cout << "\nFROM_ROS_MSG\n" << std::endl;   // Depuracion <- BORRAR

        pcl::fromROSMsg(cloud_out_, *pcrgb);

        std::cout << "\nPCRGB->AT\n" << std::endl;   // Depuracion <- BORRAR
        
        auto point = pcrgb->at(center_w_object_, center_h_object_);

        std::cout << "\nSET TF\n" << std::endl;   // Depuracion <- BORRAR

        //setTFs(point.x, point.y, point.z);
      }
      i++;
    }
  }

  void 
  Recognizer::cloudCB(const sensor_msgs::PointCloud2::ConstPtr& cloud_in)
  {
    std::cout << "\nCLOUD 1 \n" << std::endl;   // Depuracion <- BORRAR
    if (center_h_object_ < 0) {
      return;
    }

    //sensor_msgs::PointCloud2 cloud_out_;
    
    try
    {
      pcl_ros::transformPointCloud("map", *cloud_in, cloud_out_, tfListener_);
      std::cout << "\nCLOUD 2 \n" << std::endl;  // Depuracion <- BORRAR
    }
    catch(tf::TransformException & ex)
    {
      ROS_ERROR_STREAM("Transform error of sensor data: " << ex.what() << ", quitting callback");
      return;
    }

    /*std::cout << "\n\n\n\n CLOUD 4 \n\n\n\n" << std::endl;   // Depuracion <- BORRAR
    auto pcrgb = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    pcl::fromROSMsg(cloud_out_, *pcrgb);

    auto point = pcrgb->at(center_w_object_, center_h_object_);
    //setTFs(point.x, point.y, point.z);*/
    
  }

  void 
  Recognizer::setCenterObj(const int xmin, const int xmax, const int ymin, const int ymax )
  {
    center_w_object_ = xmin + (xmax - xmin) / 2;
    center_h_object_ = ymin + (ymax - ymin) / 2;

    std::cout << "\nW_CENTER: " << center_w_object_ << std::endl;
    std::cout << "H_CENTER: " << center_h_object_ << std::endl;
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
  }

  void 
  Recognizer::init() {

    if (found) {
      ROS_INFO("FOUND");

      // *** Parar de girar  <- BORRAR

    } else {
      ROS_INFO("NOT FOUND");
    }

  }
} // namespace proyecto_final