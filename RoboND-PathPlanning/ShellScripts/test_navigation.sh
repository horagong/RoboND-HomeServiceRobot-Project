#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=`rospack find add_markers`/../World/u.world" &
sleep 3

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=`rospack find add_markers`/../World/u.yaml 3d_sensor:=asus_xtion_pro" & 
sleep 3

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
