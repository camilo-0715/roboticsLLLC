#include "ejercicio_mapas/movement2.hpp"

namespace ejercicio_mapas
{
  Movement2::Movement2() 
  {

  }

  ///////////////////////////////////////////////////////

  void
  Movement2::bedroom_code_once() 
  {
    ROS_INFO("[%s] Bedroom * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::emptyroom_code_once() 
  {
    ROS_INFO("[%s] Empty room * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::gym_code_once() 
  {
    ROS_INFO("[%s] Gym * ", ros::this_node::getName().c_str());
  }

  void
  Movement2::kitchen_code_once() 
  {
    ROS_INFO("[%s] Kitchen * ", ros::this_node::getName().c_str());
  }


  bool 
  Movement2::gym_2_kitchen()
  {
    //return finished;
    return (ros::Time::now() - state_ts_).toSec() > 25.0;
  }

  bool 
  Movement2::emptyroom_2_gym()
  { 
    //return finished;
    return (ros::Time::now() - state_ts_).toSec() > 25.0;
  }

  bool 
  Movement2::kitchen_2_bedroom()
  {
    //return finished;
    return (ros::Time::now() - state_ts_).toSec() > 25.0;
  }

  bool 
  Movement2::bedroom_2_emptyroom()
  {
    
    return (ros::Time::now() - state_ts_).toSec() > 25.0;
    //return (ros::Time::now() - state_ts_).toSec() > 15.0;
  }

  

///////////////////////////////////////////////////////////////////////


} // namespace ejercicio_mapas