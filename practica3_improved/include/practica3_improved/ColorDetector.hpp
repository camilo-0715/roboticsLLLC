#ifndef PRACTICA3__COLOR_DETECTOR_HPP__
#define PRACTICA3__COLOR_DETECTOR_HPP__

#include <array>
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
  class ColorDetector
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

    // (Ball, blue, yellow) x (HSV_h, HSV_H, HSV_s)
    const std::array<std::array<int, 3>, 3> HSV_VALUES = {{{98,148,80}, {0,70,100}, {85,92,40}}};
    const int HSV_S = 255;
    const int HSV_v = 0;
    const int HSV_V = 255;
  };

} // namespace practica3

#endif // PRACTICA3__COLOR_DETECTOR_HPP__