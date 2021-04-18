#include "ejercicio_mapas/movement2.hpp"

namespace ejercicio_mapas
{
  Movement2::Movement2() : ac("move_base", true)
  {
    while(!ac.waitForServer(ros::Duration(3.0)))
    {
      ROS_INFO("waiting for the move base action server to come up");
    }

    finished = false;
  }

  ///////////////////////////////////////////////////////

  void
  Movement2::bedroom_code_once() 
  {
    ROS_INFO("[%s] Bedroom * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::emptyroom_code_once() 
  {
    ROS_INFO("[%s] Empty room * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::gym_code_once() 
  {
    ROS_INFO("[%s] Gym * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::kitchen_code_once() 
  {
    ROS_INFO("[%s] Kitchen * ", ros::this_node::getName().c_str());
  }


  bool 
  Movement2::gym_2_kitchen()
  {
    //return finished;
    return finished || (ros::Time::now() - state_ts_).toSec() > 15.0;
  }

  bool 
  Movement2::emptyroom_2_gym()
  { 
    //return finished;
    return finished || (ros::Time::now() - state_ts_).toSec() > 15.0;
  }

  bool 
  Movement2::kitchen_2_bedroom()
  {
    //return finished;
    return finished || (ros::Time::now() - state_ts_).toSec() > 15.0;
  }

  bool 
  Movement2::bedroom_2_emptyroom()
  {
    ROS_INFO("---Bedroom finish: %d", finished);
    return finished || (ros::Time::now() - state_ts_).toSec() > 15.0;
    //return (ros::Time::now() - state_ts_).toSec() > 15.0;
  }

///////////////////////////////////////////////////////////////////////

  void 
  Movement2::doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result)
  {
    ROS_INFO("finished");
    finished = true;
    ROS_INFO("finished: %d", finished);
  }

  void 
  Movement2::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
  {
    double goal_x = goal.target_pose.pose.position.x;
    double goal_y = goal.target_pose.pose.position.y;
    double current_x = feedback->base_position.pose.position.x;
    double current_y = feedback->base_position.pose.position.y;

    double difff_x = goal_x - current_x;
    double difff_y = goal_y - current_y;

    double dist = sqrt(difff_x * difff_x + difff_y * difff_y);

    ROS_INFO("distance to goal = %f", dist);
  }

  //this function moves the robot to the coords we give her as parameters
  void 
  Movement2::moveRobot(double x, double y, double orientation)
  {
    if(!isActive()) 
    {
      ROS_INFO("NO ACTIVE");
      return;
    }

    ROS_INFO("[%s] moveRobot", ros::this_node::getName().c_str());

    //we set the frame_id, stamp and new coords where the robot needs to move
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation.w = orientation;

    //we send the frame, new coords etc. to the server
    ROS_INFO("sending goal");
    ac.sendGoal(goal, boost::bind(&Movement2::doneCb, this, _1, _2), MoveBaseClient::SimpleActiveCallback(), boost::bind(&Movement2::feedbackCb, this, _1));

    ros::Rate rate(1);
    while(ros::ok() && !finished)
    {
      ROS_INFO("waiting");
      rate.sleep();
    }

    ROS_INFO("FUERA finished: %d", finished);
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("the based moved one meter forward");
    else
      ROS_INFO("the base failed to move forward one meter");
  }

} // namespace ejercicio_mapas