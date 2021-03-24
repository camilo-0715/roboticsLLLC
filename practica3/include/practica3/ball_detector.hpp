#ifndef BALLDETECTOR_H
#define BALLDETECTOR_H

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
  class ball_detector: public bica::Component
  {
  public:
      ball_detector();
      int getBallX();
      int getBallY();

  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    int ballX;
    int ballY;

    void imageCB(const sensor_msgs::Image::ConstPtr& msg);
    int BALL_HSV_h = 98;
    int BALL_HSV_H = 148;
    int BALL_HSV_s = 80;
    int BALL_HSV_S = 255;
    int BALL_HSV_v = 0;
    int BALL_HSV_V = 255;

  };
}

#endif // BALLDETECTOR_H