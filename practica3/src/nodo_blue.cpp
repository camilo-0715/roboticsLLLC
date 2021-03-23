
#include <ros/ros.h>

#include <bica/Component.h>

class BlueGoal: public bica::Component
{
public:
  BlueGoal()
  {
  }
  
  ~BlueGoal()
  {
  }
  
  /************************************************
  void setTFs(valores obtenidos de los detectores)
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

    /*******************
    avanza hacia delante
    ********************/
  }

private:
  /***************
  Las trasformadas
  ****************/
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "node_B");  

  BlueGoal goal;  
  /***********************************************************
  Aqui se podria llamar a los detectores y despues a 
  un metodo que se llame setTFs() por ejemplo que haga guarde
  las trasformada en variables private
  ************************************************************/

  ros::Rate loop_rate(7);

  while(goal.ok())
  {
    /**********************************************************
    Se puede hacer un condicional para que solo haga el giro la 
    primera vez que se reactive 
    if (el estado anterio == !isActive()) {turnTo}
    ***********************************************************/ 

  	goal.step();

  	ros::spinOnce();

  	loop_rate.sleep();
  }  

  return 0;
}
