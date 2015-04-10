#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "ps3_button_defines.h"

class TeleopVolturnus
{
public:
  TeleopVolturnus();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};


TeleopVolturnus::TeleopVolturnus()
{

  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopVolturnus::joyCallback, this);

}

void TeleopVolturnus::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist vel;
  vel.linear.x = l_scale_*joy->axes[PS3_AXIS_STICK_LEFT_UPWARDS];
  vel.linear.y = l_scale_*joy->axes[PS3_AXIS_STICK_LEFT_LEFTWARDS];
  vel.linear.z = l_scale_*joy->axes[PS3_AXIS_STICK_RIGHT_UPWARDS];  
  vel.angular.z = a_scale_*joy->axes[PS3_AXIS_STICK_RIGHT_LEFTWARDS];
  vel_pub_.publish(vel);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "ps3_controller");
  TeleopVolturnus teleop_volturnus;

  ros::spin();
}
