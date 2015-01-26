#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_broadcaster.h"
#include <string>

#define PI 3.14159265358979
enum Boolean { FALSE, TRUE };
Boolean euler_updated_=FALSE;
Boolean position_updated_=FALSE;
geometry_msgs::Point current_Euler, current_Position;


void publish_message()
{
  static tf::TransformBroadcaster br;
  
  tf::Transform transform;
  //transform.setOrigin( tf::Vector3(current_Position.x, current_Position.y, current_Position.z) );
  transform.setOrigin( tf::Vector3(current_Position.z, -current_Position.x, current_Position.y) );
  //transform.setOrigin( tf::Vector3(0, 0, 0) );
  tf::Quaternion q;
  
  q.setEuler(current_Euler.x*PI/180.0, current_Euler.z*PI/180.0, -current_Euler.y*PI/180.0);
  //q.setEuler(current_Euler.z*PI/180.0, current_Euler.x*PI/180.0, current_Euler.y*PI/180.0);
  
  /* tf::Matrix3x3 rmat;
  rmat.setEulerYPR(current_Euler.x*PI/180.0, -current_Euler.y*PI/180.0, current_Euler.z*PI/180.0);
  tf::Matrix3x3 rtrans(0,0,1,-1,0,0,0,1,0);
  rmat*=rtrans;
  rmat.getRotation(q); */
  
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
}

void eulerCallback(const geometry_msgs::Point::ConstPtr& msg)
{
   current_Euler = *msg;
   euler_updated_ = TRUE;

   if(euler_updated_ && position_updated_)
       publish_message();
}

void positionCallback(const geometry_msgs::Pose& msg)
{
   current_Position = msg.position;
   position_updated_ = TRUE;

   if(euler_updated_ && position_updated_)
       publish_message();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "volturnus_tf_publisher2");

  ros::NodeHandle nHandle1;
  ros::NodeHandle nHandle2;
  
  ros::Subscriber sub = nHandle1.subscribe("/PoseData", 10, &positionCallback);
  ros::Subscriber sub2 = nHandle2.subscribe("/eulerAngles", 10, &eulerCallback);

  ros::spin();
  return 0;
}


