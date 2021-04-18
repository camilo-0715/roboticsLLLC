#ifndef EJERCICIO_MAPAS__MOVEMENT2_HPP__
#define EJERCICIO_MAPAS__MOVEMENT2_HPP__

#include "ejercicio_mapas/coord_reader.hpp"

//importamos las librerias necesarias
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "bica/Component.h"
#include "StateMachinePr4.h"

//with this we make MoveBaseClient a nickname for actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> so whenever we need to use it  instead of writting the whole thing we use the nickname instead
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace ejercicio_mapas
{
class Movement2: public bica::StateMachinePr4
{
  public:

    Movement2();
    //this function moves the robot to the coords we give her as parameters
    void moveRobot(double x, double y,double orientation);
    bool isFinish();

    void bedroom_code_once();
    void emptyroom_code_once();
    void gym_code_once();
    void kitchen_code_once();
    
    bool bedroom_2_emptyroom();
    bool emptyroom_2_gym();
    bool gym_2_kitchen();
    bool kitchen_2_bedroom();


  private:
    ros::NodeHandle nh_;
    bool finished;
    move_base_msgs::MoveBaseGoal goal;
    //we create a MoveBaseClient type object named ac so we can send the new coords to move the robot further on
    MoveBaseClient ac;

    void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result);
    void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);
};

} // namespace ejercicio_mapas

#endif // EJERCICIO_MAPAS__MOVEMENT2_HPP__