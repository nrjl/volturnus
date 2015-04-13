//#include <stdlib.h>
//#include <stdio.h>
#include <ros/ros.h>
#include "std_msgs/Int32MultiArray.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;
double linear_gains[3], angular_gains[3];

void cmd_velCallback(const geometry_msgs::Twist& msg)
{
    std_msgs::Int32MultiArray motorCommand;

    // MOTORS:  [0]: PORT AFT
    //          [1]: PORT FORE  
    //          [2]: PORT VERTICAL  
    //          [3]: STARBOARD AFT  
    //          [4]: STARBOARD FORE  
    //          [5]: STARBOARD VERTICAL  
    motorCommand.data.assign(6,0);
    
//    if (((msg.angular.z) > 0.5) || ((msg.angular.z) < -0.5))
//    {
        motorCommand.data[0] = int (( msg.angular.z*angular_gains[0]));
        motorCommand.data[1] = int ((-msg.angular.z*angular_gains[0]));
        motorCommand.data[3] = int ((-msg.angular.z*angular_gains[0]));
        motorCommand.data[4] = int (( msg.angular.z*angular_gains[0]));
//    }
//    else if (msg.angular.z != 0.0)
//    {
//        motorCommand.data[0] = int (( msg.angular.z*angular_gains[0])/2.0);
//        motorCommand.data[1] = int ((-msg.angular.z*angular_gains[0])/2.0);
//        motorCommand.data[3] = int ((-msg.angular.z*angular_gains[0])/2.0);
//        motorCommand.data[4] = int (( msg.angular.z*angular_gains[0])/2.0);
//    }
    
    motorCommand.data[0] += int ((-msg.linear.x*linear_gains[0]));
    motorCommand.data[1] += int (( msg.linear.x*linear_gains[0]));
    motorCommand.data[3] += int ((-msg.linear.x*linear_gains[0]));
    motorCommand.data[4] += int (( msg.linear.x*linear_gains[0]));
    
    motorCommand.data[0] += int (( msg.linear.y*linear_gains[0]));
    motorCommand.data[1] += int (( msg.linear.y*linear_gains[0]));
    motorCommand.data[3] += int ((-msg.linear.y*linear_gains[0]));
    motorCommand.data[4] += int ((-msg.linear.y*linear_gains[0]));
    
    motorCommand.data[2] = int (( msg.linear.z*linear_gains[0]));
    motorCommand.data[5] = int (( msg.linear.z*linear_gains[0]));   
    
    pub.publish(motorCommand);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "volturnus_controller");

    double temp_gain = 0;
    ros::param::get("volturnus/controller_gains/linear/p", temp_gain);
    linear_gains[0] = temp_gain;
    ros::param::get("volturnus/controller_gains/linear/i", temp_gain);
    linear_gains[1] = temp_gain;
    ros::param::get("volturnus/controller_gains/linear/d", temp_gain);
    linear_gains[2] = temp_gain;
    ros::param::get("volturnus/controller_gains/angular/p", temp_gain);
    angular_gains[0] = temp_gain;
    ros::param::get("volturnus/controller_gains/angular/i", temp_gain);
    angular_gains[1] = temp_gain;
    ros::param::get("volturnus/controller_gains/angular/d", temp_gain);
    angular_gains[2] = temp_gain;
    
    ros::NodeHandle nHandpub;
    pub = nHandpub.advertise<std_msgs::Int32MultiArray>("/motorController", 10);
  
    ros::NodeHandle nHandsub;  
    ros::Subscriber sub = nHandsub.subscribe("/cmd_vel", 10, &cmd_velCallback);
    
    ros::spin();
    return 0;
}
