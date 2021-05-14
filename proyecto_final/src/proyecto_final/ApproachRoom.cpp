#include "proyecto_final/ApproachRoom.hpp"

namespace proyecto_final
{

ApproachRoom::ApproachRoom(const std::string& name, const BT::NodeConfiguration & config) 
: BT::ActionNodeBase(name, config), ac("move_base", true)
{
    arrived = false;
    sent = false;
    while(!ac.waitForServer(ros::Duration(5.0))) 
    {
      ROS_INFO("waiting for the move base action server to come up");
    }
}

void 
ApproachRoom::doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result)
{
  ROS_INFO("[APPROACH ROOM] finished");
  arrived = true;
}

void 
ApproachRoom::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{

  double goal_x = goal.target_pose.pose.position.x;
  double goal_y = goal.target_pose.pose.position.y;
  double current_x = feedback->base_position.pose.position.x;
  double current_y = feedback->base_position.pose.position.y;

  double difff_x = goal_x - current_x;
  double difff_y = goal_y - current_y;

  double dist = sqrt(difff_x * difff_x + difff_y * difff_y);

  ROS_INFO("[APPROACH ROOM] distance to goal = %f", dist);
}

void 
ApproachRoom::moveRobot(double x, double y, double orientation)
{
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = orientation;

  if (!sent){
    ROS_INFO("[APPROACH ROOM] sending goal");
    sent = true;
    ac.sendGoal(goal, boost::bind(&ApproachRoom::doneCb, this, _1, _2), MoveBaseClient::SimpleActiveCallback(), boost::bind(&ApproachRoom::feedbackCb, this, _1));
  }
  ROS_INFO("[APPROACH ROOM] Goal Sent. Waiting");
}

void
ApproachRoom::setTargetCoords(std::string destination) // set the target accorginly.
{
  if (destination.compare("bedroom") == 0){
      target_x_ = bedroom_x;
      target_y_ = bedroom_y;
  }
  else if (destination.compare("empty_room") == 0){
      target_x_ = empty_room_x;
      target_y_ = empty_room_y;
  }   
  else if (destination.compare("gym") == 0){
      target_x_ = gym_x;
      target_y_ = gym_y;
  }
  else if (destination.compare("kitchen") == 0){
      target_x_ = kitchen_x;
      target_y_ = kitchen_y;
  }
  else
  {
    ROS_INFO("NO VALID TARGET INPUTTED");
    target_x_ = 0;
    target_y_ = 0;
  }
}

void
ApproachRoom::halt()
{
  ROS_INFO("ApproachRoom halt");
}

BT::NodeStatus
ApproachRoom::tick()
{
  std::string room = getInput<std::string>("room").value(); 
  if (status() == BT::NodeStatus::IDLE)
  {
    setTargetCoords(room.c_str());
    ROS_INFO("First time in ApproachRoom");
  }
  ROS_INFO("[APPROACH ROOM] RUNNING");
  moveRobot(target_x_, target_y_, coordsData::t_orientation); 
  if (arrived){
    return BT::NodeStatus::SUCCESS; 
  }
  return BT::NodeStatus::RUNNING;
}

}  // namespace proyecto_final
