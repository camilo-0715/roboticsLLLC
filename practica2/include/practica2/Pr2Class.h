#ifndef PRACTICA2_PR2CLASS_H
#define PRACTICA2_PR2CLASS_H

namespace practica2
{
class Pr2Class  
{
  public:
    Pr2Class(): state_(GOING_FORWARD), pressed_(false);
    void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg);
    void step();

  private:
    ros::NodeHandle n_;

    static const int GOING_FORWARD   = 0;
    static const int GOING_BACK   = 1;
    static const int TURNING     = 2;

    int state_;

    bool pressed_;

    ros::Time press_ts_;
    ros::Time turn_ts_;

    ros::Subscriber sub_bumber_;
    ros::Publisher pub_vel_;

#endif  // PRACTICA2_PR2CLASS_H
