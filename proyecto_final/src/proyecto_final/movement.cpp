#include "proyecto_final/movement.hpp"

namespace proyecto_final
{
  Movement::Movement() : ac("move_base", true)
  {
    finished = false;
    while(!ac.waitForServer(ros::Duration(5.0)))
    {
      ROS_INFO("waiting for the move base action server to come up");
    }
  }

  void 
  Movement::doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result)
  {
    ROS_INFO("finished");
    finished = true;
  }

  void 
  Movement::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
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
  void 
  Movement::moveRobot(double x, double y, double orientation)
  {
    //we set the frame_id, stamp and new coords where the robot needs to move
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation.w = orientation;

    //we send the frame, new coords etc. to the server
    ROS_INFO("sending goal");
    ac.sendGoal(goal, boost::bind(&Movement::doneCb, this, _1, _2), MoveBaseClient::SimpleActiveCallback(), boost::bind(&Movement::feedbackCb, this, _1));

    ros::Rate rate(1);
    while(ros::ok() && !finished)
    {
      ROS_INFO("waiting");
      rate.sleep();
    }
  }

} // namespace proyecto_final

