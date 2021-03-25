#include "practica3/Detector.hpp"

namespace practica3 {
  Detector::Detector()
  : it_(nh_)
  {
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &Detector::imageCB, this);
  }

  void
  Detector::setObj(int obj){
    objeto = obj;
  }

  int 
  Detector::getX(){
		if (objeto == 1){
			return ballX;
		} 
		else if (objeto == 2){
			return bGoalX;
		}
    else{
			return yGoalX;
		}
  }

  int 
  Detector::getY(){
    if (objeto == 1){
			return ballY;
		} 
		else if (objeto == 2){
			return bGoalY;
		}
    else{
			return yGoalY;
		}
  }

	void
	Detector::getPos(cv::Mat hsv, int color[])
	{
		int height = hsv.rows;
    int width = hsv.cols;
    int step = hsv.step;
    int channels = 3;  // HSV

    int x = 0;
    int y = 0;
    int counter = 0;
    
    for (int i = 0; i < height; i++ ){
      for (int j = 0; j < width; j++ )
      {
        int posdata = i * step + j * channels;

        if ((hsv.data[posdata] >= color[0]) &&
             (hsv.data[posdata] <= color[1]) &&
            (hsv.data[posdata+1] >= color[2]) &&
             (hsv.data[posdata+1] <= HSV_S) &&
            (hsv.data[posdata+2] >= HSV_v) &&
             (hsv.data[posdata+2] <= HSV_V))
        {
          x += j;
          y += i;
          counter++;
        }
      }  
		}

		if (counter > 0){

			if (objeto == 1){
				ballX = x / counter;
				ballY = y / counter;
			} 
			else if (objeto == 2){
				bGoalX = x / counter;
				bGoalY = y / counter;
			}
			else{
				yGoalX = x / counter;
				yGoalY = y / counter;
			}
		
		}

      
		else{   

			if (objeto == 1){
				ballX = -1;
				ballY = -1;
			} 
			else if (objeto == 2){
				bGoalX = -1;
				bGoalY = -1;
			}
			else{
				yGoalX = -1;
				yGoalY = -1;
			}
		}
	}

	
  void 
  Detector::imageCB(const sensor_msgs::Image::ConstPtr& msg)
  {
   
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::Mat hsv;
    cv::cvtColor(cv_ptr->image, hsv, CV_RGB2HSV);

	getPos(hsv, RED);

  }
}
  
