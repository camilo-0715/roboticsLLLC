#include "practica2/DetectDodge.h"

namespace practica2
{

  DetectDodge::DetectDodge()
  : state_(GOING_FORWARD), detect_object_left_(false), detect_object_right_(false), detect_object_center_(false)
  {
    sub_laser_ = n.subscribe("/scan", 1, &DetectDodge::laserCallback, this);
    pub_vel_ = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
    marker_pub = n.advertise<visualization_msgs::MarkerArray>("/visualization_marker", 1);
  }

  void
  DetectDodge::laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
  {
    int rightObjectCounter = 0;
    int leftObjectCounter = 0;
    int centerObjectCounter = 0;

    for (int i = 0; i < msg->ranges.size(); i++)
    {
      if (msg->ranges[i] < OBSTACLE_DISTANCE)
      {
        rightObjectCounter++;
      }
      else if (i < (msg->ranges.size()/3)*2)
      {
        if (msg->ranges[i] < OBSTACLE_DISTANCE)
        {
          centerObjectCounter++;
        }
      }
      else
      {
        if (msg->ranges[i] < OBSTACLE_DISTANCE)
        {
          leftObjectCounter++;
        }
      }
    }

    detect_object_left_ = (leftObjectCounter > (msg->ranges.size()/3)/2);
    detect_object_center_ = (centerObjectCounter > (msg->ranges.size()/3)/2);
    detect_object_right_ = (rightObjectCounter > (msg->ranges.size()/3)/2);

    if (detect_object_left_)
    {
      ROS_INFO("OBJECT LEFT");
    }
    if (detect_object_center_)
    {
      ROS_INFO("OBJECT CENTER");
    }
    if (detect_object_right_)
    {
      ROS_INFO("OBJECT RIGHT");
    }
  }

  void
  DetectDodge::step()
  {
    geometry_msgs::Twist cmd;

    switch (state_)
    {
      case GOING_FORWARD:

        cmd.linear.x = 1;
        cmd.linear.z = 0;

        if (detect_object_right_ || detect_object_left_ || detect_object_center_)
        {
          detect_ts_ = ros::Time::now();
          state_ = GOING_BACK;
          ROS_INFO("GOING_FORWARD -> GOING_BACK");
        }
        break;

      case GOING_BACK:

        cmd.linear.x = -1; //camilo: no se si poner numeros negativos aqui funcionará para ir para atras
        cmd.linear.z = 0;

        if ((ros::Time::now() - detect_ts_).toSec() > BACKING_TIME )
        {
          turn_ts_ = ros::Time::now();
          state_ = TURNING;
          ROS_INFO("GOING_BACK -> TURNING");
        }
        break;

      case TURNING:

        cmd.linear.x = 0;
        cmd.angular.z = 20; //camilo: no se cuantos grados es esto, hay que comprobarlo con el simulador

        if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
        {
          state_ = GOING_FORWARD;
          ROS_INFO("TURNING -> GOING_FORWARD");
        }
          break;
    }

    pub_vel_.publish(cmd);
  }


  void 
  DetectDodge::initMarkers()
  {
    // marker: izuierda; marker2: centro; marker3: derecha
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0.25;
    marker.pose.position.y = -0.43;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    //msg.lifetime = ros::Duration(1.0);

    visualization_msgs::Marker marker2;
    marker2 = marker;
    marker2.id = 1;
    marker2.pose.position.x = 0.5;
    marker2.pose.position.y = 0;

    visualization_msgs::Marker marker3;
    marker3 = marker; 
    marker3.id = 2;  
    marker3.pose.position.x = 0.25;
    marker3.pose.position.y = 0.43;

    // Cambio de color
    if(detect_object_left_){
      marker.color.r = 1.0;
      marker.color.g = 0.0;
    }
    if(detect_object_center_){
      marker2.color.r = 1.0;
      marker2.color.g = 0.0;
    }
    if(detect_object_right_){
      marker3.color.r = 1.0;
      marker3.color.g = 0.0;
    }

    visualization_msgs::MarkerArray marker_array;
    marker_array.markers.resize(3);
    marker_array.markers[0] = marker;
    marker_array.markers[1] = marker2;
    marker_array.markers[2] = marker3;

    marker_pub.publish(marker_array);
    
  }
}