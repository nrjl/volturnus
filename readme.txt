README FOR VOLTURNUS ROS PACKAGES. UBUNTU!!!!

// You need ROS Indigo, just google it.
// (http://wiki.ros.org/indigo/Installation/Ubuntu)

// ROS PACKAGES:
sudo apt-get install ros-indigo-tf ros-indigo-gmapping ros-indigo-rviz 
ros-indigo-navigation ros-indigo-rosbridge-server ros-indigo-joy

// UNITY SIM
// You need to get the unity sim from Jeff's dropbox account. Currently,
// the launch file expects it to be installed in $HOME/vLBV/unity_sim. I
// have it connected to my dropbox account, so I created a symlink to that
// location:
ln -s $HOME/Dropbox/vLBV\ sim/ $HOME/vLBV/unity_sim

// VOLTURNUS PACKAGES
// Two are available on GitHub, but the serial packages are not due to IP
// agreements. The serial packages currently live on Nick's desktop (nautilus)
// which has an RDML user (ask Nick for the password). You need to be inside
// the OSU network to access nautilus.

// Make catkin directories if you don't already have a catkin workspace.
cd ~
mkdir catkin_ws
cd catkin_ws
mkdir src
cd src

git clone https://github.com/nrjl/volturnus.git OR
git clone ssh://user@10.214.152.144//home/nick/catkin_ws/src/volturnus

git clone https://github.com/nrjl/volturnus_2dnav.git OR
git clone ssh://user@10.214.152.144//home/nick/catkin_ws/src/volturnus_2dnav

git clone ssh://user@10.214.152.144//home/nick/catkin_ws/src/volturnus_serial

cd ~/catkin_ws
catkin_make

// PS3 CONTROLLER STUFF
// Get ros software
rosdep install ps3joy

// Pair it (ony need to do this once). Plug it in with USB, then:
sudo bash
rosrun ps3joy sixpair
// It should set the master bluetooth address of the controller to your computer
// exit the sudo environment (type exit or press ctrl-d), disconnect USB cable
// You might need to add yourself to the uucp group to access tty (serial ports)
sudo usermod -a -G uucp <user>

// run in a new command window (it will stay active as long as the controller is
// connected and being used):
rosrun ps3joy ps3joy.py
// Click the PS button in the middle of the controller, then you should get a
// message of "Connection activated"

// RUN THINGS!

// run the volturnus script:
// SIM ONLY
cd ~/catkin_ws/src/volturnus
./run-volturnus-sim

// WITH THE PS3 CONTROLLER:
// Activate connection with ps3 controller (see above)
cd ~/catkin_ws/src/volturnus
./run-volturnus-ps3

// SERIAL CONNECTION

// Simulation/debugging, create a virtual serial port:
sudo apt-get install socat
mkdir ~/dev
socat -x -v PTY,link=$HOME/dev/modem0 PTY,link=$HOME/dev/modem1

// Copy the serial_params.
// Set the "port" value in catkin_ws/src/volturnus_serial/serial_params_local.yaml
// to your serial port (or use the virtual one at $HOME/dev/modem0)
rosparam load "$(rospack find volturnus_serial)/serial_params.yaml" serial_test

// Run the ROS serial publisher
rosrun volturnus_serial serial_test




