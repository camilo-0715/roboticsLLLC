
#include <ros/ros.h>

#include <bica/Component.h>

class Ball: public bica::Component
{
public:
  Ball()
  {
  }
  
  ~Ball()
  {
  }
  
  /************************************************
  void setCoord(valores obtenidos de los detectores)
  {
    establece los valores de las TFs
  }
  **************************************************/

  /************************************************
  void turnTo()
  {
    if(!isActive()) return;

    hace el giro para ponerse de frente a la porteria
    segun los valores de las TFs
  }
  **************************************************/

  void step()
  {
  	if(!isActive()) return;

    // Depuración luego se quita
  	ROS_INFO("[%s]", ros::this_node::getName().c_str());

    /******
    avanza
    *******/
  }

private:
  /******************************************
  variables con las coordenadas de la pelota
  *******************************************/
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node_B");  

  Ball ball;  

  ros::Rate loop_rate(7);
  while(ball.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo detecte la pelota
    y haga el giro la primera vez que se reactive 
    if (el estado anterio == !isActive()) {setCoord();turnTo();}
    ***********************************************************/ 
  	ball.step();

  	ros::spinOnce();

  	loop_rate.sleep();
  }  

  return 0;
}
