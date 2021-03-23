cmake_minimum_required(VERSION 3.0.2)
project(practica3)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  bica
  cv_bridge
  geometry_msgs
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  roslint
  tf
  pcl_conversions
  pcl_ros
)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package(
  CATKIN_DEPENDS
  roscpp
  sensor_msgs
  std_msgs
  tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

link_directories(
	${PCL_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})


add_executable(nodo_p3 src/nodo_p3.cpp
)
target_link_libraries(nodo_p3 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(yellow_detector src/yellow_detector.cpp)
target_link_libraries(yellow_detector ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})



add_dependencies(nodo_p3 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



roslint_cpp(
  src/yellow_detector.cpp
  src/nodo_p3.cpp.cpp
)