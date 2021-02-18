cmake_minimum_required(VERSION 2.8.3)
project(practica1)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  roslint
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(nodo_sub_bumper src/nodo_sub_bumper.cpp)
add_executable(nodo_pub_vel src/nodo_pub_vel.cpp)

target_link_libraries(nodo_sub_bumper ${catkin_LIBRARIES})
target_link_libraries(nodo_pub_vel ${catkin_LIBRARIES})

roslint_cpp(
  src/nodo_sub_bumper.cpp
  src/nodo_pub_vel.cpp
)
