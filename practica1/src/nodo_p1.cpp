#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "kobuki_msgs/BumperEvent.h"

bool bump;

void messageCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  printf("Linear\n\tx: %f\n", msg->linear.x);
  printf("\ty: %f\n", msg->linear.y);
  printf("\tz: %f\n", msg->linear.z);
  printf("Angular\n\tx: %f\n", msg->angular.x);
  printf("\ty: %f\n", msg->angular.y);
  printf("\tz: %f\n", msg->angular.z);
  
}
void bumperProcess(const kobuki_msgs::BumperEvent bumperMessage)
{
  if (bumperMessage.state == kobuki_msgs::BumperEvent::PRESSED) {bump = true;}
  else {bump = false;} 
}    

int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_subscriber");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/mobile_base/commands/velocity", 1, messageCallback);
  ros::Subscriber sub2 = n.subscribe("/mobile_base/events/bumper", 1, bumperProcess);

  ros::Publisher num_pub1 = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Rate loop_rate(40);

  while (ros::ok())
  {
    geometry_msgs::Twist msg1;

    if (bump){msg1.linear.x = 0;}
    else {msg1.linear.x = 1;}

    num_pub1.publish(msg1);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}