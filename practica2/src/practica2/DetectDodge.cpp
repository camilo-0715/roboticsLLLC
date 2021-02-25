#include "practica2/DetectDodge.h"
#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"


namespace practica2
{
  DetectDodge::DetectDodge(): state_(GOING_FORWARD), pressed_(false)
  {
      ros::init(argc, argv, "num_subscriber");
      ros::NodeHandle n;

      ros::Subscriber sub_bumper = n.subscribe("/mobile_base/events/bumper", 1, bumperProcess); //camilo: estoy hay que cambiarlo para subscribirse al laser en vez de al buumper
      ros::Rate loop_rate(40);

      // pub_vel_ = n_.advertise<...>(...)
      ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  }


  void DetectDodge::bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
  {
    // pressed_ = (...); //aqui hay

    //  ...
  }

  void DetectDodge::step()
  {
    geometry_msgs::Twist cmd;

    switch (state_)
    {
    case GOING_FORWARD:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;

      cmd.linear.x = 1;
      cmd.linear.z = 0;

      if (pressed_)
      {
        press_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }
      break;

    case GOING_BACK:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;

      cmd.linear.x = -1; //camilo: no se si poner numeros negativos aqui funcionará para ir para atras
      cmd.linear.z = 0;

      if ((ros::Time::now() - press_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        state_ = TURNING;
        ROS_INFO("GOING_BACK -> TURNING");
      }
      break;

    case TURNING:
      // cmd.linear.x = ...;
      // cmd.angular.z = ...;

      cmd.linear.x = 0;
      cmd.linear.z = 30; //camilo: no se cuantos grados es esto, hay que comprobarlo con el simulador

      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING -> GOING_FORWARD");
      }
      break;
    }

    // pub_vel_.publish(...);
  }
} // namespace practica2