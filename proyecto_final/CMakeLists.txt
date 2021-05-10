cmake_minimum_required(VERSION 3.0.2)
project(proyecto_final)
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
  tf2
  tf2_ros
  geometry_tf
  pcl_conversions
  pcl_ros
  darknet_ros_msgs
  actionlib
  behaviortree_cpp_v3
)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
catkin_package(
  CATKIN_DEPENDS
  roscpp
  sensor_msgs
  std_msgs
  tf
  tf2
  tf2_ros
  geometry_tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
  darknet_ros_msgs
  actionlib
  behaviortree_cpp_v3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/coord_reader.cpp
  src/${PROJECT_NAME}/movement.cpp
  src/${PROJECT_NAME}/dn_recognizing.cpp
)

link_directories(
	${PCL_LIBRARY_DIRS}
)
add_definitions(${PCL_DEFINITIONS})

add_executable(nodo_reconocimiento src/nodo_reconocimiento.cpp 
  src/proyecto_final/dn_recognizing.cpp
)
target_link_libraries(nodo_reconocimiento ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_reconocimiento ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(nodo_behavior_tree src/nodo_behavior_tree.cpp 
  src/proyecto_final/ApproachObject.cpp
  src/proyecto_final/ApproachRoom.cpp
  src/proyecto_final/TurnTo.cpp
  src/proyecto_final/inRoom.cpp
  src/proyecto_final/dn_recognizing.cpp
)
target_link_libraries(nodo_behavior_tree ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})


roslint_cpp(
  src/proyecto_final/coord_reader.cpp
  include/proyecto_final/coord_reader.hpp

  src/proyecto_final/movement.cpp
  include/proyecto_final/movement.hpp

  src/proyecto_final/dn_recognizing.cpp
  include/proyecto_final/dn_recognizing.hpp

  src/proyecto_final/ApproachObject.cpp
  include/proyecto_final/ApproachObject.hpp
  
  src/proyecto_final/ApproachRoom.cpp
  include/proyecto_final/ApproachRoom.hpp

  src/proyecto_final/TurnTo.cpp
  include/proyecto_final/TurnTo.hpp

  src/proyecto_final/inRoom.cpp
  include/proyecto_final/inRoom.hpp

)