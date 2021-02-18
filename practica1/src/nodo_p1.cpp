#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

void messageCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  printf("Linear\n\tx: %f\n", msg->linear.x);
  printf("\ty: %f\n", msg->linear.y);
  printf("\tz: %f\n", msg->linear.z);
  printf("Angular\n\tx: %f\n", msg->angular.x);
  printf("\ty: %f\n", msg->angular.y);
  printf("\tz:  %f\n", msg->angular.z);
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_subscriber");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/mobile_base/commands/velocity", 1, messageCallback);
  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    geometry_msgs::Twist msg;

    msg.linear.x = 0.5;
    num_pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}