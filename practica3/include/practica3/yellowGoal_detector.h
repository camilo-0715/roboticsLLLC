#ifndef YELLOWGOALDETECTOR_H
#define YELLOWGOALDETECTOR_H

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
  class yellowGoal_detector: public bica::Component
  {
  public:
      yellowGoal_detector();
      int getYGoalX();
      int getYGoalY();

  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    int yGoalX;
    int yGoalY;


    void imageCB(const sensor_msgs::Image::ConstPtr& msg);

    int YELLOWGOAL_HSV_h = 85;
    int YELLOWGOAL_HSV_H = 92;
    int YELLOWGOAL_HSV_s = 40;
    int YELLOWGOAL_HSV_S = 255;
    int YELLOWGOAL_HSV_v = 0;
    int YELLOWGOAL_HSV_V = 255;
  };
}

#endif // YELLOWGOALDETECTOR_H