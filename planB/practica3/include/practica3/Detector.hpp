#ifndef PRACTICA3__DETECTOR_HPP__
#define PRACTICA3__DETECTOR_HPP__

#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Float32.h>
#include <bica/Component.h>

namespace practica3
{
  class Detector: public bica::Component
  {
  public:
    Detector();

    int getX(); 
    int getY();
    void setObj(int obj);  // Qué objeto quiere detectar -> 1: bola, 2: portería azul, 3: portería amarilla


  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    // Bola
    int ballX = -1;
    int ballY = -1;

    // Portería amarilla
    int yGoalX = -1;
    int yGoalY = -1;

    // Portería azul
    int bGoalX = -1;
    int bGoalY = -1;

    int objeto;  // Objeto a detectar: 1-> bola, 2->blue, 3-> yellow

    void imageCB(const sensor_msgs::Image::ConstPtr& msg);
    void getPos(cv::Mat hsv, int color[]);  // Obtener las posiciones del objeto


    //HSV_h,HSV_H,HSV_s
    int RED[3] = {98,148,80};   // ¡¡¡¡¡HAY QUE CAMBIAR LA FORMA DE PONER LOS VECTORES!!!!
    int YELLOW[3] = {85,92,40};
    int BLUE[3] = {0,70,100};

    int HSV_S = 255;
    int HSV_v = 0;
    int HSV_V = 255;
  };
}

#endif // PRACTICA3__DETECTOR_HPP__