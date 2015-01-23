#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_broadcaster.h"
#include <string>

void poseCallback(const geometry_msgs::Pose& msg)
{
  static tf::TransformBroadcaster br;
  geometry_msgs::Point pp=msg.position;
  geometry_msgs::Quaternion qq=msg.orientation;
  
  tf::Transform transform;
  //transform.setOrigin( tf::Vector3(pp.z, -pp.x, pp.y) );
  transform.setOrigin( tf::Vector3(pp.x, pp.y, pp.z) );
  tf::Quaternion q(qq.x, qq.y, qq.z, qq.w);
  //tf::Matrix3x3 rmat(q);
  //tf::Matrix3x3 rtrans(0,0,1,-1,0,0,0,1,0);
  //rmat*=rtrans;
  // rmat.getRotation(q);
  // double roll, pitch, yaw;
  // tf::Matrix3x3(q).getEulerYPR(yaw, pitch, roll);
  // q.setEuler(yaw, -pitch, -roll);
  //tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
  //q.setRPY(roll, yaw, pitch);  
  //q.setRPY(roll, pitch, yaw);    
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "volturnus_tf_publisher");

  ros::NodeHandle nHandle;
  
  ros::Subscriber sub = nHandle.subscribe("/PoseData", 10, &poseCallback);

  ros::spin();
  return 0;
}
