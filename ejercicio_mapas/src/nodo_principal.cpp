#include "ejercicio_mapas/coord_reader.hpp"

//importamos las librerias necesarias
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//with this we make MoveBaseClient a nickname for actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> so whenever we need to use it  instead of writting the whole thing we use the nickname instead
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

bool finished = false;
move_base_msgs::MoveBaseGoal goal;

void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result)
{
  ROS_INFO("finished");
  finished = true;
}

void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{

  double goal_x = goal.target_pose.pose.position.x;
  double goal_y = goal.target_pose.pose.position.y;
  double current_x = feedback->base_position.pose.position.x;
  double current_y = feedback->base_position.pose.position.y;

  double difff_x = goal_x - current_x;
  double difff_y = goal_y - current_y;

  double dist = sqrt(difff_x* difff_x + difff_y * difff_y);

  ROS_INFO("distance to goal = %f", dist);
}

//this function moves the robot to the coords we give her as parameters
void MoveRobot(double x, double y,double orientation)
{
  //we create a MoveBaseClient type object named ac so we can send the new coords to move the robot further on
  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("waiting for the move base action server to come up");
  }

  //we set the frame_id, stamp and new coords where the robot needs to move
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = orientation;

  //we send the frame, new coords etc. to the server
  ROS_INFO("sending goal");
  ac.sendGoal(goal,doneCb);

  ros::Rate rate(1);
  while(ros::ok() && !finished)
  {
    ROS_INFO("waiting");
    rate.sleep();
  }

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("the based moved one meter forward");
  else
    ROS_INFO("the base failed to move forward one meter");

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ejercicio_mapas");

  ejercicio_mapas::CoordReader coord;


  double x = coord.getX();
  double y = coord.getY();

  ROS_INFO("target coordinates: (%f, %f)", x, y);
  MoveRobot(x,y,1.0);

  ros::spin();

  return 0;
}
