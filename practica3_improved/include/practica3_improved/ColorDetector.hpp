#ifndef PRACTICA3__COLOR_DETECTOR_HPP__
#define PRACTICA3__COLOR_DETECTOR_HPP__

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
  class ColorDetector: public bica::Component
  {
  public:
      ColorDetector();
      int getX(int object);
      int getY(int object);
      void findObjectColor(int object);

  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    cv::Mat hsv;

    int bGoalX;
    int bGoalY;

    int yGoalX;
    int yGoalY;

    int ballX;
    int ballY;

    void imageCB(const sensor_msgs::Image::ConstPtr& msg);

    // Ball, blue, yellow
    //HSV_h, HSV_H, HSV_s
    int HSV_VALUES[3][3] = {{98,148,80},{0,70,100},{85,92,40}};
    int HSV_S = 255;
    int HSV_v = 0;
    int HSV_V = 255;
  };
}

#endif // PRACTICA3__COLOR_DETECTOR_HPP__