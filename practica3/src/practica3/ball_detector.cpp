#include "practica3/ball_detector.h"

namespace practica3 {
  ball_detector::ball_detector()
  : it_(nh_)
  {
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ball_detector::imageCB, this);
  }

  int 
  ball_detector::getBallX(){
    return ballX;
  }

  int 
  ball_detector::getBallY(){
    return ballY;
  }

  void 
  ball_detector::imageCB(const sensor_msgs::Image::ConstPtr& msg)
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

        if ((hsv.data[posdata] >= BALL_HSV_h) &&
             (hsv.data[posdata] <= BALL_HSV_H) &&
            (hsv.data[posdata+1] >= BALL_HSV_s) &&
             (hsv.data[posdata+1] <= BALL_HSV_S) &&
            (hsv.data[posdata+2] >= BALL_HSV_v) &&
             (hsv.data[posdata+2] <= BALL_HSV_V))
        {
          x += j;
          y += i;
          counter++;
        }
      }  
      if (counter > 0){
          ballX = x/counter;
          ballY = y/counter;
          
      }
      else{   
        ballX = -1;
        ballY = -1;
      }
  }
}
