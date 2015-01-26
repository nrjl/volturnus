#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"

#define PI 3.14159265358979
enum Boolean { FALSE, TRUE };
Boolean euler_updated_=FALSE;
Boolean position_updated_=FALSE;
Boolean twist_updated_=FALSE;

geometry_msgs::Point current_Euler, current_Position;
geometry_msgs::Twist current_Twist;

ros::Publisher pub;

void publish_message()
{
  //static tf::TransformBroadcaster br;
  
  geometry_msgs::TransformStamped odom_trans;
  
  odom_trans.transform.translation.x = current_Position.z;
  odom_trans.transform.translation.y = -current_Position.x;
  odom_trans.transform.translation.z = current_Position.y;
    
  tf::Quaternion tf_quat;  
  tf_quat.setEuler(current_Euler.x*PI/180.0, current_Euler.z*PI/180.0, -current_Euler.y*PI/180.0);
  
  geometry_msgs::Quaternion geo_Quat;
  tf::quaternionTFToMsg(tf_quat, geo_Quat);
  odom_trans.transform.rotation = geo_Quat;

  odom_trans.header.stamp = ros::Time::now();
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";

  //br.sendTransform(odom_trans);


  nav_msgs::Odometry odom;
  odom.header.stamp = odom_trans.header.stamp;
  odom.header.frame_id = "odom";

  //set the position
  odom.pose.pose.position.x = odom_trans.transform.translation.x;
  odom.pose.pose.position.y = odom_trans.transform.translation.y;
  odom.pose.pose.position.z = odom_trans.transform.translation.z;
  odom.pose.pose.orientation = geo_Quat;

  //set the velocity
  odom.child_frame_id = "base_link";
  odom.twist.twist.linear.x = current_Twist.linear.z;
  odom.twist.twist.linear.y =-current_Twist.linear.x;
  odom.twist.twist.linear.z = current_Twist.linear.y;

  odom.twist.twist.angular.x=-current_Twist.angular.y;
  odom.twist.twist.angular.y= current_Twist.angular.z;
  odom.twist.twist.angular.z= current_Twist.angular.x;

  //publish the message
  pub.publish(odom);
  
}

void eulerCallback(const geometry_msgs::Point::ConstPtr& msg)
{
   current_Euler = *msg;
   euler_updated_ = TRUE;

   if(twist_updated_ && position_updated_)
       publish_message();
}

void positionCallback(const geometry_msgs::Pose& msg)
{
   current_Position = msg.position;
   position_updated_ = TRUE;

   if(euler_updated_ && twist_updated_)
       publish_message();
}

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
   current_Twist = *msg;
   
   twist_updated_ = TRUE;

   if(euler_updated_ && position_updated_)
       publish_message();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle nHandle1;
  ros::NodeHandle nHandle2;
  ros::NodeHandle nHandle3;
  ros::NodeHandle nHandle4;  
  
  pub = nHandle4.advertise<nav_msgs::Odometry>("odom", 50);
  ros::Subscriber sub = nHandle1.subscribe("/PoseData", 10, &positionCallback);
  ros::Subscriber sub2 = nHandle2.subscribe("/eulerAngles", 10, &eulerCallback);
  ros::Subscriber sub3 = nHandle3.subscribe("/VelocityData", 10, &twistCallback);
  
  ros::spin();
  return 0;
}


