#ifndef PROYECTO_FINAL__MOVEMENT_HPP__
#define PROYECTO_FINAL__MOVEMENT_HPP__

#include "proyecto_final/coord_reader.hpp"

//importamos las librerias necesarias
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//with this we make MoveBaseClient a nickname for actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> so whenever we need to use it  instead of writting the whole thing we use the nickname instead
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace proyecto_final
{
class Movement
{
  public:

    Movement();
    //this function moves the robot to the coords we give her as parameters
    void moveRobot(double x, double y,double orientation);

  private:
    ros::NodeHandle nh_;
    bool finished = false;
    move_base_msgs::MoveBaseGoal goal;
    //we create a MoveBaseClient type object named ac so we can send the new coords to move the robot further on
    MoveBaseClient ac;

    void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result);
    void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);

};

} // namespace proyecto_final

#endif // PROYECTO_FINAL__MOVEMENT_HPP__ 