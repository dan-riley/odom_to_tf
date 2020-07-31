#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

std::string newFrame;
std::string orgFrame;

void odomCallback(const nav_msgs::OdometryPtr& msg) {
  if ((msg->pose.pose.position.x != 0) &&
      (msg->pose.pose.position.y != 0) &&
      (msg->pose.pose.position.z != 0)) {
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->pose.pose.position.x,
                                    msg->pose.pose.position.y,
                                    msg->pose.pose.position.z));
    tf::Quaternion q = tf::Quaternion(msg->pose.pose.orientation.x,
             msg->pose.pose.orientation.y,
             msg->pose.pose.orientation.z,
             msg->pose.pose.orientation.w);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), orgFrame, newFrame));
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "odom_to_tf", ros::init_options::AnonymousName);
  ros::NodeHandle nh("~");

  std::string odomTopic;
  nh.param<std::string>("odomTopic", odomTopic, "/Base/neighbors/H01/odometry");
  nh.param<std::string>("newFrame", newFrame, "H01_frame");
  nh.param<std::string>("orgFrame", orgFrame, "world");
  ros::Subscriber sub_odom = nh.subscribe(odomTopic, 10, &odomCallback);

  ros::spin();
  return 0;
}
