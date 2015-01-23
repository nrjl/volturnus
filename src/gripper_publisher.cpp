#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

#include <sstream>


/**
 * A simple publisher to publish the 
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "gripper_joints");

  ros::NodeHandle nHandle;

  // Create the publisher, topic volturnus/grip_joint with queue size 100
  ros::Publisher gripper_pub = nHandle.advertise<sensor_msgs::JointState>("volturnus/grip_joint", 100);

  // Publish at 10Hz
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    sensor_msgs::JointState msg;

    std::stringstream ss;
    ss << "joint_gripper1";
    msg.name = ss.str();
    
    msg.position = 0.0;
    msg.velocity = 0.0;
    msg.effort = 0.0;

    gripper_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
