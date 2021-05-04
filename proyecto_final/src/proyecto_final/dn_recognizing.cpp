#include "proyecto_final/dn_recognizing.hpp"

namespace proyecto_final
{
  Recognizer::Recognizer(std::string item_in) : item(item_in)
  {
    std::cout << "ITEM: " << item << std::endl; // Depuracion <- BORRAR

    obj_sub_ = nh_.subscribe("/darknet_ros/bounding_boxes", 1, &Recognizer::checkForObjectsResultCB, this);

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
      }
      i++;
    }
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