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
    // (-pi/5, 0, pi/5) = angle_min + angle_increment* index_ranges
    // Solving for the previous formula, we obtain:
    // index_ranges = ((-pi/5, 0, pi/5) - angle_min) / angle_increment
    int indexMinusPiFifths = static_cast<int>((((PI/5)- msg->angle_min))/msg->angle_increment);
    int indexPiFifths = static_cast<int>((((-PI/5)- msg->angle_min))/msg->angle_increment);
    int indexZero = msg->ranges.size()/2;

    detect_object_left_ = msg->ranges[indexPiFifths] < OBSTACLE_DISTANCE;
    detect_object_center_ = msg->ranges[indexMinusPiFifths] < OBSTACLE_DISTANCE;
    detect_object_right_ = msg->ranges[indexZero] < OBSTACLE_DISTANCE;

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
        cmd.angular.z = 0;

        if (detect_object_right_ || detect_object_left_ || detect_object_center_)
        {
          detect_ts_ = ros::Time::now();
          state_ = GOING_BACK;
          ROS_INFO("GOING_FORWARD -> GOING_BACK");
        }
        break;

      case GOING_BACK:

        cmd.linear.x = -0.5/BACKING_TIME; 
        cmd.linear.z = 0;
        cmd.angular.z = 0;

        if ((ros::Time::now() - detect_ts_).toSec() > BACKING_TIME )
        {
          turn_ts_ = ros::Time::now();
          state_ = TURNING;
          ROS_INFO("GOING_BACK -> TURNING");
        }
        break;

      case TURNING:
        // Randomly rotate between [30, 90], as it rotates 3s the angular velocity will be between [0.39, 0.52]
        srand(time(NULL));
        float angle = (rand () % 14 + 39)/100;// rand () % (N-M+1) + M;  This will be between M y N

        cmd.linear.x = 0;
        cmd.angular.z = angle;

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
    visualization_msgs::Marker left_marker;
    left_marker.header.frame_id = "base_link";
    left_marker.header.stamp = ros::Time();
    left_marker.ns = "my_namespace";
    left_marker.id = 0;
    left_marker.type = visualization_msgs::Marker::SPHERE;
    left_marker.action = visualization_msgs::Marker::ADD;
    left_marker.pose.position.x = 0.29;
    left_marker.pose.position.y = 0.4;
    left_marker.pose.position.z = 0;
    left_marker.pose.orientation.x = 0.0;
    left_marker.pose.orientation.y = 0.0;
    left_marker.pose.orientation.z = 0.0;
    left_marker.pose.orientation.w = 1.0;
    left_marker.scale.x = 0.1;
    left_marker.scale.y = 0.1;
    left_marker.scale.z = 0.1;
    left_marker.color.a = 1.0; // Don't forget to set the alpha!
    left_marker.color.r = 0.0;
    left_marker.color.g = 1.0;
    left_marker.color.b = 0.0;
    //msg.lifetime = ros::Duration(1.0);

    visualization_msgs::Marker center_marker;
    center_marker = left_marker;
    center_marker.id = 1;
    center_marker.pose.position.x = 0.5;
    center_marker.pose.position.y = 0;

    visualization_msgs::Marker right_marker;
    right_marker = left_marker; 
    right_marker.id = 2;  
    right_marker.pose.position.x = 0.29;
    right_marker.pose.position.y = -0.4;

    // Change color
    if(detect_object_left_){
      left_marker.color.r = 1.0;
      left_marker.color.g = 0.0;
    }
    if(detect_object_center_){
      center_marker.color.r = 1.0;
      center_marker.color.g = 0.0;
    }
    if(detect_object_right_){
      right_marker.color.r = 1.0;
      right_marker.color.g = 0.0;
    }

    visualization_msgs::MarkerArray marker_array;
    marker_array.markers.resize(3);
    marker_array.markers[0] = left_marker;
    marker_array.markers[1] = center_marker;
    marker_array.markers[2] = right_marker;

    marker_pub.publish(marker_array);
    
  }
}