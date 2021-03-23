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
      switch (state_)
      {
        case BALL:
          removeDependency("nodo_ball");
          addDependency("nodo_blue");

          state_++;

          break;

        case BLUE:
          removeDependency("nodo_blue");
          addDependency("nodo_yellow");

          state_++;

          break;

        case YELLOW:
          removeDependency("nodo_yellow");
          addDependency("nodo_turn");

          state_++;

          break;

        case TURN:
          removeDependency("nodo_turn");
          addDependency("nodo_ball");

          state_ = 0;
          break;
      }

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