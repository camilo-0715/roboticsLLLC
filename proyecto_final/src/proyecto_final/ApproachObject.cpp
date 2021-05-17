#include "proyecto_final/ApproachObject.hpp"

namespace proyecto_final
{

ApproachObject::ApproachObject(const std::string& name, const BT::NodeConfiguration & config) // as we have the inFront node, this should just be a straightforward
: BT::ActionNodeBase(name, config), buffer_(), listener_(buffer_)
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  // laser_sub_ = nh_.subscribe("/scan", 1, &ApproachObject::laser_callback, this);
  reached_object = false;
}


void
ApproachObject::checkDistance(){
    geometry_msgs::TransformStamped map2bfpMsg; // transform the data from map to bf to obtain robot coords.   
    geometry_msgs::TransformStamped map2ObjectMsg;

    try {
      map2bfpMsg = buffer_.lookupTransform("map","base_footprint", ros::Time(0)); 
    } catch (std::exception & e) {
      ROS_INFO("EXCEPTION BF");
      return;
    } 
    try {
      map2ObjectMsg = buffer_.lookupTransform("map",getInput<std::string>("object").value(), ros::Time(0)); 
    } catch (std::exception & e) {
      ROS_INFO("EXCEPTION OBJ");
      return;
    } 

    tf2::Stamped<tf2::Transform> map2bf;
    tf2::Stamped<tf2::Transform> map2obj;

    tf2::fromMsg(map2bfpMsg, map2bf);
    tf2::fromMsg(map2ObjectMsg, map2obj);

    tf2::Vector3 robotVect = map2bf.getOrigin(); // vector stores the coords, so we take the ones we need.
    tf2::Vector3 objectVect = map2obj.getOrigin();

    robot_x_ = robotVect.getX(); 
    robot_y_ = robotVect.getY();

    object_x_ = objectVect.getX(); 
    object_y_ = objectVect.getY();

    ROS_INFO("ObjectX: %f, ObjectY: %f", object_x_, object_y_);
    ROS_INFO("RobotX: %f, RobotY: %f", robot_x_, robot_y_);

    if ((abs(object_x_ - robot_x_) < 0.5)&&((abs(object_y_ - robot_y_) < 0.5))){
      reached_object = true;
    }
  }
/*
void
ApproachObject::laser_callback(const sensor_msgs::LaserScan::ConstPtr msg)
{
  for(int i = (msg->ranges.size() / 2) - 20; i < (msg->ranges.size() / 2) + 20; i++)
  {
    if(msg->ranges[i] < 0.5)
    {
      reached_object = true;
    }
  }
}
*/

void
ApproachObject::move()
{
    geometry_msgs::Twist cmd;

    cmd.linear.x = 0.5;
    ROS_INFO("Move");
    vel_pub_.publish(cmd);
    checkDistance();

  if (reached_object)
  {
    ROS_INFO("reaches object");
    reached_object = true;
    cmd.linear.x = 0;
    vel_pub_.publish(cmd);
  }

}

void
ApproachObject::halt() // walk to the object. we can use the poincloud to check the distance and not hit it that way.
{
  ROS_INFO("ApproachObject halt");
}

BT::NodeStatus
ApproachObject::tick()
{
  ROS_INFO("Aproach tick");
  move();
  if( reached_object) 
  {
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    return BT::NodeStatus::RUNNING;
  }
  
}
  
}  // namespace proyecto_final
