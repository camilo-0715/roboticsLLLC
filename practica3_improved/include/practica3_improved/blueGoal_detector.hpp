#ifndef BLUEGOALDETECTOR_H
#define BLUEGOALDETECTOR_H

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
  class blueGoal_detector: public bica::Component
  {
  public:
      blueGoal_detector();
      int getBGoalX();
      int getBGoalY();

  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    int bGoalX;
    int bGoalY;

    void imageCB(const sensor_msgs::Image::ConstPtr& msg);

    int BLUEGOAL_HSV_h = 0;
    int BLUEGOAL_HSV_H = 70;
    int BLUEGOAL_HSV_s = 100;
    int BLUEGOAL_HSV_S = 255;
    int BLUEGOAL_HSV_v = 0;
    int BLUEGOAL_HSV_V = 255;
  };
}

#endif // BLUEGOALDETECTOR_H