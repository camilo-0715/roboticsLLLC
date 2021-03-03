cmake_minimum_required(VERSION 2.8.3)
project(practica2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  kobuki_msgs
  roslint
  visualization_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(nodo_p2 
  src/nodo_p2.cpp
  src/practica2/DetectDodge.cpp
)

target_link_libraries(nodo_p2 ${catkin_LIBRARIES})

roslint_cpp(
  src/nodo_p2.cpp
  include/practica2/DetectDodge.h src/practica2/DetectDodge.cpp
)
