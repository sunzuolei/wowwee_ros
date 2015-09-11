# The WowWee driver based on ROS ÔºàRobot Operation SystemÔº?
## The package of rovio_base
-------------------------
#### encapsulated some of WowWee Rovio APIS as follow functions:
* ManualDrive()
* GetMCUReport()
* GetImage()

#### How to use the package of rovio_base
* Create a rovio_ws workspace for catkin
```
mkdir -p ~/rovio_ws/src
cd ~/rovio_ws/src
catkin_init_workspace
cd ~/rovio_ws/
catkin_make
source devel/setup.bash (To make sure the workspace is in your ROS environment variable)
```
* Copy the rovio_base package to ~/rovio_ws/src/
* Build the workspace
```
cd ~/rovio_ws/
catkin_make
```
* run the node of rovio_base, roslaunch the Server
```
roslaunch rovio_base rovioServer.launch
```

## The package of rovio_test
The Rovio WowWee would head middle and head down, and you would view the images from camera 2 seconds.
#### How to use the package of rovio_test
* Copy the rovio_test package to ~/rovio_ws/src/
* Build the workspace
```
cd ~/rovio_ws/
catkin_make   (if you get the error tell you "rovio_base/manDrv.h: No file or directory", Please source ~/rovio_ws/setup.bash)
```

## The package of obstacle_avoidence
The Rovio WowWee would avoid the obstacle and keep moving.
#### How to use the package of obstacle_avoidence
* Copy the obstacle_avoidence package to ~/rovio_ws/src/
* Build the workspace
```
cd ~/rovio_ws/
catkin_make   (if you get the error tell you "rovio_base/manDrv.h: No file or directory", Please source ~/rovio_ws/setup.bash)
```

## The package of rovio_keyboard
The Rovio WowWee could be controlled by keyboard.
#### How to use the package of obstacle_avoidence
* Copy the rovio_keyboard package to ~/rovio_ws/src/
* Build the workspace
```
cd ~/rovio_ws/
catkin_make   (if you get the error tell you "rovio_base/manDrv.h: No file or directory", Please source ~/rovio_ws/setup.bash)
```

## How to run the package of rovio_test„ÄÅobstacle„ÄÅrovio_keyboard
* run the follow commands in three terminals respectively
```
roscore
roslaunch rovio_base rovioService.launch
rosrun rovio_test rovioTest
(rosrun obstacle_avoidence obstacleAvoidence)
(rosrun rovio_keyboard roviokeyboard)
```

## References
-------------------
This work would be impossible without the excellent open source projects:
* [Rovio WowWee driver API](http://kujo.cs.pitt.edu/cs1567/index.php/CPP_API) from University of Pittsburgh
* [The driver and based on ROS by yuanboshe](http://github.com/yuanboshe/rovio_base)
* [The package of obstacle avoidence by yuanboshe ](http://github.com/yuanboshe/rovio_obstacle_avoidence)

## Contributor
-------------------
- ’≈◊”—Û: [zzy@mpig.com.cn](zzy@mpig.com.cn)

---------
Cheers!
:panda_face:
