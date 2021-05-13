#include "proyecto_final/TurnTo.hpp"

/* Uso de la clase Recognizer para girar hasta que encuentre el objeto
   y establezca la tf devuelve success cuando la tf a sido colocada 
   si aun no se ha detectado el objeto devuelve running y si no se puede 
   alcanzar encontrar failure <-BORRAR
*/
namespace proyecto_final
{

TurnTo::TurnTo(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), recognizer_(getInput<std::string>("object").value())
{
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  tf_set = false;
}

void
TurnTo::halt() // LUISMI: Couldnt try, my pc sucks
{
  ROS_INFO("TurnTo halt");
}

/*
void 
TurnTo::init( const std::string& obj)
{
  obj_ = obj;
}*/

void
TurnTo::turn()
{
  geometry_msgs::Twist msg;
  msg.angular.z = 0.5;
  vel_pub_.publish(msg);
}

void
TurnTo::stop()
{
  geometry_msgs::Twist msg;
  msg.angular.z = 0.0;
  vel_pub_.publish(msg);
}

BT::NodeStatus
TurnTo::tick()
{
  if (tf_set)
    return BT::NodeStatus::SUCCESS;
    
  ROS_INFO("TurnTo tick");
  turn();

  if (recognizer_.foundObj()) 
  {
    stop();
    tf_set = true;
    return BT::NodeStatus::SUCCESS;
  } 
  else 
  {
    return BT::NodeStatus::RUNNING;
  }
  
}

}  // namespace proyecto_final
