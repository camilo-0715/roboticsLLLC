// 2021-03-24 Lucia
// Ejemplo de uso de tfs

#include <string>
#include <math.h>

#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"

#include "geometry_tf/transforms.h"

#include "ros/ros.h"

class Detector
{
public:
  Detector()
  : buffer_(), listener_(buffer_) 
  {}

  void publish_detection(float x, float y)
  {
    geometry_msgs::TransformStamped odom2bf_msg;
    try{
      odom2bf_msg = buffer_.lookupTransform("odom", "base_footprint", ros::Time(0));
    } catch (std::exception & e){
      return;
    }

    tf2::Stamped<tf2::Transform> odom2bf;
    tf2::fromMsg(odom2bf_msg, odom2bf);

    tf2::Stamped<tf2::Transform> bf2object;
    bf2object.setOrigin(tf2::Vector3(x, y, 0));
    bf2object.setRotation(tf2::Quaternion(0, 0, 0, 1));

    tf2::Transform odom2object = odom2bf * bf2object;

    geometry_msgs::TransformStamped odom2object_msg;
    odom2object_msg.header.stamp = ros::Time::now();
    odom2object_msg.header.frame_id = "odom";
    odom2object_msg.child_frame_id = "object";

    odom2object_msg.transform = tf2::toMsg(odom2object);

    broadcaster.sendTransform(odom2object_msg);

    geometry_msgs::TransformStamped bf2obj_2_msg;
    try{
      bf2obj_2_msg = buffer_.lookupTransform("base_footprint", "object", ros::Time(0));
    } catch (std::exception & e){
      return;
    }

    double angle = atan2(bf2obj_2_msg.transform.translation.y, bf2obj_2_msg.transform.translation.x);

    std::cerr << "angle = "  << angle << std::endl;
  }

private:
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  tf2_ros::TransformBroadcaster broadcaster;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tf_sub");
  ros::NodeHandle n;

  Detector detector;

  ros::Rate loop_rate(1);

  float x = 1;
  float y = 0;

  while (ros::ok())
  {
    y += 0.01;
    detector.publish_detection(x, y);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
