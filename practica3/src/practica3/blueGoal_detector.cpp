#include "practica3/blueGoal_detector.hpp"

namespace practica3 {
  blueGoal_detector::blueGoal_detector()
  : it_(nh_)
  {
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &blueGoal_detector::imageCB, this);
  }

  int 
  blueGoal_detector::getBGoalX(){
    return bGoalX;
  }

  int 
  blueGoal_detector::getBGoalY(){
    return bGoalY;
  }

  void 
  blueGoal_detector::imageCB(const sensor_msgs::Image::ConstPtr& msg)
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

        if ((hsv.data[posdata] >= BLUEGOAL_HSV_h) &&
             (hsv.data[posdata] <= BLUEGOAL_HSV_H) &&
            (hsv.data[posdata+1] >= BLUEGOAL_HSV_s) &&
             (hsv.data[posdata+1] <= BLUEGOAL_HSV_S) &&
            (hsv.data[posdata+2] >= BLUEGOAL_HSV_v) &&
             (hsv.data[posdata+2] <= BLUEGOAL_HSV_V))
        {
          x += j;
          y += i;
          counter++;
        }
      }  
      if (counter > 0){
          bGoalX = x/counter;
          bGoalY = y/counter;
      }
      else{   
        bGoalX = -1;
        bGoalY = -1;
      }
  }
}
  
