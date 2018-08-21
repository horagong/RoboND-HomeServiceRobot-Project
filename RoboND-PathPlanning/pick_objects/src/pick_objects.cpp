#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/String.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  ros::NodeHandle n;
  ros::Publisher status_pub = n.advertise<std_msgs::String>("status", 1000);
  ros::Rate loop_rate(1);
  std_msgs::String msg;

  //publish status
  msg.data = "START";
  status_pub.publish(msg);
  ros::spinOnce();

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -4.25;
  goal.target_pose.pose.position.y = 7.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending the pick-up location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Arrived at the pick-up location");
  else
    ROS_INFO("Failed to arrive at the pick-up location");

  //update status
  msg.data = "PICKED-UP";
  status_pub.publish(msg);
  ros::spinOnce();

  sleep(5);



  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 3.25;
  goal.target_pose.pose.position.y = 7.0;
  goal.target_pose.pose.orientation.w = 3.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending the drop-off location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Arrived at the drop-off location");
  else
    ROS_INFO("Failed to arrive at the drop-off location");

  //update status
  msg.data = "DROPPED-OFF";
  status_pub.publish(msg);
  ros::spin();

  return 0;
}
