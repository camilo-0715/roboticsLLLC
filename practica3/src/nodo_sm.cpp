#include "ros/ros.h"
#include <bica/Component.h>
#include "practica3/ball_operator.hpp"
#include "practica3/blueGoal_operator.hpp"
#include "practica3/yellowGoal_operator.hpp"
#include "practica3/Turn.hpp"


#define CHANGE_TIME 10
#define TURN_TIME 5.0


class StateMachine: public bica::Component
{
public:
	StateMachine()
	{
    state_ = INITIAL;
	}

	void step(practica3::ball_detector bdt, 
            practica3::Ball ball, 
            practica3::blueGoal_detector bgdt, 
            practica3::BlueGoal blueGoal, 
            practica3::yellowGoal_detector ygdt, 
            practica3::YellowGoal yellowGoal,
            practica3::Turn turn)
	{
		if (!isActive()) return;    
    switch (state_)
    { 
      case INITIAL: // sin este estado habia un bug que no ffuncionaba el estado de la petota.
        state_ = BALL;
        start = ros::Time::now();
        break;

      case BALL:
        ROS_INFO("BOLA");
        if (ball.turnTo(bdt) == 0) // si devuelve 0 significa que la tiene enfrente, se mueve
          ball.step();

        if ((ros::Time::now() - start).toSec() >= CHANGE_TIME){
          start = ros::Time::now();
          state_ = BLUE;
          ROS_INFO("BALL -> BGOAL");
        }
        break;
      
      case BLUE:
        ROS_INFO("AZUL");
        if (blueGoal.turnTo(bgdt) == 0)
          blueGoal.step();

        if ((ros::Time::now() - start).toSec() >= CHANGE_TIME){
          start = ros::Time::now();
          state_ = YELLOW;
          ROS_INFO("BGOAL -> YGOAL");
        }
        break;

      case YELLOW:
        ROS_INFO("YELLOW");
        if (yellowGoal.turnTo(ygdt) == 0)
          yellowGoal.step();

        if ((ros::Time::now() - start).toSec() >= CHANGE_TIME){
          start = ros::Time::now();
          state_ = TURN;
          ROS_INFO("YGOAL -> TURN");
        }
        break;

      case TURN:
        ROS_INFO("TURN");
        turn.step();
        if ((ros::Time::now() - start).toSec() >= TURN_TIME){
          start = ros::Time::now();
          state_ = BALL;
          ROS_INFO("TURN -> BALL");
        }
        break;
    }  
  }

private:
  ros::Time start;
  ros::NodeHandle n;
  geometry_msgs::Twist cmd;

  int state_;
  enum {INITIAL,BALL, BLUE, YELLOW, TURN};
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica3");

  StateMachine st;
  practica3::ball_detector ballDetector;
  practica3::Ball ballOperator;
  practica3::blueGoal_detector blueGoalDetector;
  practica3::BlueGoal blueGoalOperator;
  practica3::yellowGoal_detector yellowGoalDetector;
  practica3::YellowGoal yellowGoalOperator;
  practica3::Turn turnOperator;

  ros::Rate loop_rate(30);

	while(st.ok())
	{
		st.step(ballDetector, ballOperator, blueGoalDetector, blueGoalOperator, yellowGoalDetector, yellowGoalOperator, turnOperator);

		ros::spinOnce();
		loop_rate.sleep();
	}
  
  return 0;
}