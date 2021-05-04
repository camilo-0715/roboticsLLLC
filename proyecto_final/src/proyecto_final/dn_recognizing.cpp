#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{
  Recognizer::Recognizer(std::string item_in) : item(item_in), buffer_(), listener_(buffer_)
  {
    std::cout << "ITEM: " << item << std::endl; // Depuracion <- BORRAR

    obj_sub_ = nh_.subscribe("/darknet_ros/bounding_boxes", 1, &Recognizer::checkForObjectsResultCB, this);
    cloud_sub_ = nh_.subscribe("/camera/depth/points", 1, &Recognizer::cloudCB, this);

    std::cout << "THERE" << std::endl;  // Depuracion <- BORRAR
  }

  void 
  Recognizer::checkForObjectsResultCB(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
  {
    int i = 0;
    found = false;

    std::cout << "[CallBack] Received bounding boxes." << std::endl;

    num_classes = msg->bounding_boxes.size();
    std::cout << "[CallBack] NUM: " << num_classes << std::endl;  // Depuracion <- BORRAR

    // Va recorriendo todos los objectos detectados hasta que encuentra uno que coincida
    // con el que hemos elegido y tiene un porcentaje mayor de 50%   <- BORRAR
    while (i < num_classes && !found) {
      std::cout << msg->bounding_boxes[i].Class << " == " << item << std::endl;  // Depuracion <- BORRAR
      std::cout << "PROBABILITY: " << msg->bounding_boxes[i].probability << std::endl;  // Depuracion <- BORRAR
      if (msg->bounding_boxes[i].Class == item && msg->bounding_boxes[i].probability > 0.5) {
        found = true;

        std::cout << "XMIN: " << msg->bounding_boxes[i].xmin << std::endl;  // Depuracion <- BORRAR
        std::cout << "XMAX: " << msg->bounding_boxes[i].xmax << std::endl;  // Depuracion <- BORRAR
        std::cout << "YMIN: " << msg->bounding_boxes[i].ymin << std::endl;  // Depuracion <- BORRAR
        std::cout << "YMAX: " << msg->bounding_boxes[i].ymax << std::endl;  // Depuracion <- BORRAR
        setCenterObj(msg->bounding_boxes[i].xmin, msg->bounding_boxes[i].xmax, msg->bounding_boxes[i].ymin, msg->bounding_boxes[i].ymax);
        setTFs();
      }
      i++;
    }
  }

  void 
  Recognizer::cloudCB(const sensor_msgs::PointCloud2::ConstPtr& cloud_in)
  {
    // no hay necesidad de hacer este callback si aun no se ha encontrado 
    // el objeto que se busca <- BORRAR
    if (center_h_object_ < 0) {
      return;
    }

    sensor_msgs::PointCloud2 cloud;
    
    // Cambio de frame a camera_link <- BORRAR
    try
    {
      pcl_ros::transformPointCloud("camera_link", *cloud_in, cloud, tfListener_);
    }
    catch(tf::TransformException & ex)
    {
      ROS_ERROR_STREAM("Transform error of sensor data: " << ex.what() << ", quitting callback");
      return;
    }

    // Se crea la nube de puntos <- BORRAR
    auto pcrgb = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    pcl::fromROSMsg(cloud, *pcrgb);

    // Se obtiene el punto <- BORRAR
    std::cout << "W_CENTER: " << center_w_object_ << std::endl;  // Depuracion <- BORRAR
    std::cout << "H_CENTER: " << center_h_object_ << std::endl;  // Depuracion <- BORRAR
    auto point = pcrgb->at(center_w_object_, center_h_object_);

    std::cout << "DISTANCE (X, Y, Z): (" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl; // Depuracion <- BORRAR
    distances_[0] = point.x;
    distances_[1] = point.y;
    distances_[2] = point.z;
  }

  void 
  Recognizer::setCenterObj(const int xmin, const int xmax, const int ymin, const int ymax )
  {
    // Calculo el punto central del objeto 
    //
    // Lo comento con un dibujito:
    // H************************************
    // E*******xmin----------ymax***********
    // I*******|                |***********
    // H*******|     OBJETO     |***********
    // G*******|                |***********
    // T*******[xmax-  ]        |***********
    // ********[xmin/2 ]        |***********
    // ********ymin-----------xmax**********
    // ********************************WIDTH <- BORRAR
    
    
    center_w_object_ = xmin + (xmax-xmin)/2;
    center_h_object_ = ymin + (ymax-ymin)/2;
  }

  void 
  Recognizer::setTFs()
  {
    geometry_msgs::TransformStamped odom2bf_msg;
    
    try {
      odom2bf_msg = buffer_.lookupTransform("odom","base_footprint", ros::Time(0)); // esta excepcion salta constantemente y no puedo crear la transformada.
    } catch (std::exception & e) {
      return;
    }
    
    tf2::Stamped<tf2::Transform> odom2bf;
    tf2::fromMsg(odom2bf_msg, odom2bf);

    tf2::Stamped<tf2::Transform> bf2Obj;

    bf2Obj.setOrigin(tf2::Vector3(distances_[0], distances_[1], 0));
    bf2Obj.setRotation(tf2::Quaternion(0, 0, 0, 1));

    tf2::Transform odom2Obj = odom2bf * bf2Obj;

    geometry_msgs::TransformStamped odom2Obj_msg;

    odom2Obj_msg.header.stamp = ros::Time::now();
    odom2Obj_msg.header.frame_id = "odom";
    odom2Obj_msg.child_frame_id = item;

    odom2Obj_msg.transform = tf2::toMsg(odom2Obj);

    broadcaster_.sendTransform(odom2Obj_msg);
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