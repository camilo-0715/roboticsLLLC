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

class Goal_tf
{
public:
  Goal_tf()
  : buffer_(), listener_(buffer_) 
  {}

  void publish_Goal_tf(float x, float y)
  {
    geometry_msgs::TransformStamped bf2odom_msg;
    try{
      bf2odom_msg = buffer_.lookupTransform("base_footprint","odom", ros::Time(0));
    } catch (std::exception & e){
      return;
    }

    tf2::Stamped<tf2::Transform> bf2odom;
    tf2::fromMsg(bf2odom_msg, bf2odom);

    tf2::Stamped<tf2::Transform> odom2Goal;

    odom2Goal.setOrigin(tf2::Vector3(x, y, 0));
    odom2Goal.setRotation(tf2::Quaternion(0, 0, 0, 1));

    tf2::Transform bf2Goal = bf2odom * odom2Goal;

    geometry_msgs::TransformStamped bf2Goal_msg;

    bf2Goal_msg.header.stamp = ros::Time::now();
    bf2Goal_msg.header.frame_id = "odom";
    bf2Goal_msg.child_frame_id = "Goal";

 

    bf2Goal_msg.transform = tf2::toMsg(bf2Goal);


    broadcaster.sendTransform(bf2Goal_msg);


    geometry_msgs::TransformStamped bf2Goal_2_msg;

    try{
      bf2Goal_2_msg = buffer_.lookupTransform("base_footprint", "Goal", ros::Time(0));
    } catch (std::exception & e){
      return;
    }

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

  Goal_tf Goal_tf;

  ros::Rate loop_rate(1);

  float x = 1;
  float y = 0;

  while (ros::ok())
  {
    Goal_tf.publish_Goal_tf(x, y);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
