
#include <ros/ros.h>

#include <bica/Component.h>


/*******************************
Esto se puede rellenar con el turn
que se estaba haciendo
********************************/
class Turn: public bica::Component
{
public:
  Turn()
  {
  }
  
  ~Turn()
  {
  }
  
  void step()
  {
  	if(!isActive()) return;

    // Depuración luego se quita
  	ROS_INFO("[%s]", ros::this_node::getName().c_str());

    /****
    giro
    *****/
  }

private:
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node_B");  

  Turn turn;  

  ros::Rate loop_rate(7);
  while(turn.ok())
  {
  	turn.step();

  	ros::spinOnce();

  	loop_rate.sleep();
  }  

  return 0;
}
