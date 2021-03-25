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
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/Turn.cpp
  src/${PROJECT_NAME}/LaserDetector.cpp
  src/${PROJECT_NAME}/Detector.cpp
  src/${PROJECT_NAME}/Operator.cpp
)

link_directories(
	${PCL_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})


# NODO DETECTOR  -- COLOR
add_executable(nodo_detector src/nodo_detector.cpp
src/${PROJECT_NAME}/Detector.cpp
)
target_link_libraries(nodo_detector ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_detector ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



# NODO SM
add_executable(nodo_sm src/nodo_sm.cpp
src/practica3/Operator.cpp
src/practica3/Turn.cpp
src/practica3/LaserDetector.cpp
src/practica3/Detector.cpp
)
target_link_libraries(nodo_sm ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_sm ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


# NODO LASER
add_executable(nodo_laser src/nodo_laser.cpp
src/practica3/LaserDetector.cpp
)
add_dependencies(nodo_laser ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(nodo_laser ${catkin_LIBRARIES})


roslint_cpp(
  src/practica3/Turn.cpp
  src/practica3/Detector.cpp
  src/practica3/Operator.cpp
  src/practica3/LaserDetector.cpp


  include/practica3/Turn.hpp
  include/practica3/Operator.hpp
  include/practica3/Detector.hpp
  include/practica3/LaserDetector.hpp

  
  src/nodo_ms.cpp
  src/nodo_laser.cpp
  src/nodo_turn.cpp
  src/nodo_detector.cpp
)
