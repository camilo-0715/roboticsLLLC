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
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/coord_reader.cpp
  src/${PROJECT_NAME}/movement.cpp
)

link_directories(
	${PCL_LIBRARY_DIRS}
)
add_definitions(${PCL_DEFINITIONS})

add_executable(nodo_reconocimiento src/nodo_reconocimiento.cpp 
  src/proyecto_final/coord_reader.cpp
  src/proyecto_final/movement.cpp
)

target_link_libraries(nodo_reconocimiento ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_reconocimiento ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

roslint_cpp(

  src/proyecto_final/coord_reader.cpp
  include/proyecto_final/coord_reader.hpp

  src/proyecto_final/movement.cpp
  include/proyecto_final/movement.hpp

)