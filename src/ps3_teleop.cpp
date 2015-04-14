#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "ps3_button_defines.h"

// Class for our ps3 publisher
class TeleopVolturnus
{
    public:
      TeleopVolturnus();

    private:
      void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
      
      ros::NodeHandle nh;

      int forward_axis, strafe_axis, vertical_axis, bearing_axis;
      double linear_gain, angular_gain;
      ros::Publisher cmdvel_pub;
      ros::Subscriber joy_sub;  
};

// Constructor creates the node handle, sets the scales and creates handles
// to the subscriber and publisher
TeleopVolturnus::TeleopVolturnus():
    forward_axis(PS3_AXIS_STICK_LEFT_UPWARDS),
    strafe_axis(PS3_AXIS_STICK_LEFT_LEFTWARDS),
    vertical_axis(PS3_AXIS_STICK_RIGHT_UPWARDS),
    bearing_axis(PS3_AXIS_STICK_RIGHT_LEFTWARDS),
    angular_gain(1.0),
    linear_gain(1.0)
{
    nh.param<double>("angular_gain", angular_gain, angular_gain);
    nh.param<double>("linear_gain", linear_gain, linear_gain);
    nh.param<int>("forward_axis", forward_axis, forward_axis);
    nh.param<int>("strafe_axis", strafe_axis, strafe_axis);
    nh.param<int>("vertical_axis", vertical_axis, vertical_axis);
    nh.param<int>("bearing_axis", bearing_axis, bearing_axis);

    cmdvel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("/joy", 10, &TeleopVolturnus::joyCallback, this);
}

// Callback
void TeleopVolturnus::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist vel;
  vel.linear.x = linear_gain*joy->axes[forward_axis];
  vel.linear.y = linear_gain*joy->axes[strafe_axis];
  vel.linear.z = linear_gain*joy->axes[vertical_axis];  
  vel.angular.z = angular_gain*joy->axes[bearing_axis];
  cmdvel_pub.publish(vel);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ps3_teleop");
  TeleopVolturnus teleop_volturnus;

  ros::spin();
}
