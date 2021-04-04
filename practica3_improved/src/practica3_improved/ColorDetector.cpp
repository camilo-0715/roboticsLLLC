#include "practica3_improved/ColorDetector.hpp"

namespace practica3 {
  ColorDetector::ColorDetector()
  : it_(nh_)
  {
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ColorDetector::imageCB, this);
  }

  int 
  ColorDetector::getX(int object){
    if(object == 0){
      return ballX;
    }
    else if (object == 1){
      return bGoalX;
    }
    else{
      return yGoalX;
    }
  }

  int 
  ColorDetector::getY(int object){
    if(object == 0){
      return ballY;
    }
    else if (object == 1){
      return bGoalY;
    }
    else{
      return yGoalY;
    }
  }

  void 
  ColorDetector::findObjectColor(int object){
    int height = hsv.rows;
    int width = hsv.cols;
    int step = hsv.step;
    int channels = 3;  // HSV

    int x = 0;
    int y = 0;
    int X; 
    int Y;
    int counter = 0;

    for (int i=0; i < height; i++ )
      for (int j=0; j < width; j++ )
      {
        int posdata = i * step + j * channels;

        if ((hsv.data[posdata] >= HSV_VALUES[object][0]) &&
             (hsv.data[posdata] <= HSV_VALUES[object][1]) &&
            (hsv.data[posdata+1] >= HSV_VALUES[object][2]) &&
             (hsv.data[posdata+1] <= HSV_S) &&
            (hsv.data[posdata+2] >= HSV_v) &&
             (hsv.data[posdata+2] <= HSV_V))
        {
          x += j;
          y += i;
          counter++;
        }
      }  
      if (counter > 0){
        X = x / counter;
        Y = y / counter;
      }
      else{   
        X = -1;
        Y = -1;
      }

      if(object == 0){
        ballX = X;
        ballY = Y;
      }
      else if (object == 1){
        bGoalX = X;
        bGoalY = Y;
      }
      else{
        yGoalX = X;
        yGoalY = Y;
      }
  }

  void 
  ColorDetector::imageCB(const sensor_msgs::Image::ConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::cvtColor(cv_ptr->image, hsv, CV_RGB2HSV);    
  }
} //practica3
  
