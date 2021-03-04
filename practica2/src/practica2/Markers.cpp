#include "practica2/Markers.h"
#include "practica2/DetectDodge.h"

namespace practica2
{
  Markers::Markers()
  {
    marker_pub = n.advertise<visualization_msgs::MarkerArray>("/visualization_marker", 1);
  }

  void 
  Markers::initMarkers()
  {
    // marker: izuierda; marker2: centro; marker3: derecha
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 1;
    marker.pose.position.y = -1;
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
    marker2.pose.position.x = 1;
    marker2.pose.position.y = 0;

    visualization_msgs::Marker marker3;
    marker3 = marker; 
    marker3.id = 2;  
    marker3.pose.position.x = 1;
    marker3.pose.position.y = 1;

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