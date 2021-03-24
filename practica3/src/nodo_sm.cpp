#include "ros/ros.h"
#include <bica/Component.h>

#define CHANGE_TIME 30.0

class StateMachine: public bica::Component
{
public:
	StateMachine()
	{
    state_ = 0;
    addDependency("nodo_ball");

    start = ros::Time::now();
	}

	~StateMachine()
	{
	}

	void step()
	{
		if (!isActive()) return;

    if((ros::Time::now()-start).toSec() > CHANGE_TIME){
      if(state_ == 0){
				removeDependency("nodo_ball");
        addDependency("nodo_blue");  

        state_ = BLUE; 
      } else if(state_ == 1){
        removeDependency("nodo_blue");
        addDependency("nodo_yellow");  

        state_ = YELLOW;
      } else if(state_ == 2){
        removeDependency("nodo_yellow");
        addDependency("Turn");  

        state_ = TURN;  
      } else if(state_ == 3){
        removeDependency("Turn");
        addDependency("nodo_ball");  

        state_ = BALL; 
      }
      start = ros::Time::now();
      // Esto simplemente es para depurar por si acaso nos hace falta luego se quita
      ROS_INFO("[%s] step estate: %d", ros::this_node::getName().c_str(), state_);
    }
  }

private:
  ros::Time start;

  int state_;
  enum {BALL, BLUE, YELLOW, TURN};
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "practica3");
  ros::NodeHandle n;

  StateMachine st;

  ros::Rate loop_rate(7);

	while(st.ok())
	{
		st.step();

		ros::spinOnce();
		loop_rate.sleep();
	}
  
  return 0;
}