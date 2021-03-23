#include "practica3/yellowGoal_detector.h"

namespace practica3 {
  yellowGoal_detector::yellowGoal_detector()
  : it_(nh_)
  {
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &yellowGoal_detector::imageCB, this);
  }

  int 
  yellowGoal_detector::getYGoalX(){
    return yGoalX;
  }

  int 
  yellowGoal_detector::getYGoalY(){
    return yGoalY;
  }
  void 
  yellowGoal_detector::imageCB(const sensor_msgs::Image::ConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::Mat hsv;
    cv::cvtColor(cv_ptr->image, hsv, CV_RGB2HSV);

    int height = hsv.rows;
    int width = hsv.cols;
    int step = hsv.step;
    int channels = 3;  // HSV

    int x = 0;
    int y = 0;
    int counter = 0;

    for (int i=0; i < height; i++ )
      for (int j=0; j < width; j++ )
      {
        int posdata = i * step + j * channels;

        if ((hsv.data[posdata] >= YELLOWGOAL_HSV_h) &&
             (hsv.data[posdata] <= YELLOWGOAL_HSV_H) &&
            (hsv.data[posdata+1] >= YELLOWGOAL_HSV_s) &&
             (hsv.data[posdata+1] <= YELLOWGOAL_HSV_S) &&
            (hsv.data[posdata+2] >= YELLOWGOAL_HSV_v) &&
             (hsv.data[posdata+2] <= YELLOWGOAL_HSV_V))
        {
          x += j;
          y += i;
          counter++;
        }
      }  
      if (counter > 0){
          yGoalX = x/counter;
          yGoalY = y/counter;
          ROS_INFO("x: %d", yGoalX);
          ROS_INFO("y: %d", yGoalY);
      }
      else{   
        yGoalX = -1;
        yGoalY = -1;
      }
  }
}
