cmake_minimum_required(VERSION 2.8.3)
project(volturnus)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS 
  roscpp
  rospy
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf
)

###################################
## catkin specific configuration ##
###################################
catkin_package(CATKIN_DEPENDS
  roscpp 
  std_msgs 
  sensor_msgs 
  geometry_msgs 
  nav_msgs
  tf
)

###########
## Build ##
###########

include_directories( ${catkin_INCLUDE_DIRS} )

# add_executable(gripper_publisher src/gripper_publisher.cpp)
# target_link_libraries(gripper_publisher ${catkin_LIBRARIES})
# add_dependencies(gripper_publisher ${catkin_EXPORTED_TARGETS})

add_executable(volturnus_tf_publisher src/volturnus_tf_publisher.cpp)
target_link_libraries(volturnus_tf_publisher ${catkin_LIBRARIES})
add_dependencies(volturnus_tf_publisher ${catkin_EXPORTED_TARGETS})

add_executable(volturnus_tf_publisher2 src/volturnus_tf_publisher2.cpp)
target_link_libraries(volturnus_tf_publisher2 ${catkin_LIBRARIES})
add_dependencies(volturnus_tf_publisher2 ${catkin_EXPORTED_TARGETS})

add_executable(odometry_publisher src/odometry_publisher.cpp)
target_link_libraries(odometry_publisher ${catkin_LIBRARIES})
add_dependencies(odometry_publisher ${catkin_EXPORTED_TARGETS})

add_executable(laser_tf_publisher src/laser_tf_publisher.cpp)
target_link_libraries(laser_tf_publisher ${catkin_LIBRARIES})
add_dependencies(laser_tf_publisher ${catkin_EXPORTED_TARGETS})

add_executable(laser_republisher src/laser_republisher.cpp)
target_link_libraries(laser_republisher ${catkin_LIBRARIES})
add_dependencies(laser_republisher ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS volturnus volturnus_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_volturnus.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
