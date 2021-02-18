#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  ros::NodeHandle n;

  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/command/velocity", 1);

  ros::Rate loop_rate(10);

  int count=0;

  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x = 1;

    num_pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
 }