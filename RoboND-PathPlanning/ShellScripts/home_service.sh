#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=`rospack find add_markers`/../World/u.world" &
sleep 3

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=`rospack find add_markers`/../World/u.yaml" &
sleep 3

xterm -e "rosrun rviz rviz -d `rospack find add_markers`/../RvizConfig/home_service.rviz " &
sleep 3

xterm -e "rosrun add_markers add_markers " &
sleep 3

xterm -e "rosrun pick_objects pick_objects "
