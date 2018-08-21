#!/bin/sh
xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=`rospack find wall_follower`/../World/u.world" &
sleep 3

xterm  -e  "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=`rospack find wall_follower`/launch/gmapping.launch" & 
sleep 3

xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3

xterm  -e  "rosrun wall_follower wall_follower"
