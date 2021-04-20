cmake_minimum_required(VERSION 3.0.2)
project(ejercicio_mapas)
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
  fsm
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/coord_reader.cpp
  src/${PROJECT_NAME}/movement.cpp
  src/${PROJECT_NAME}/part2_state_machine.cpp
  src/${PROJECT_NAME}/gym.cpp
  src/${PROJECT_NAME}/kitchen.cpp
  src/${PROJECT_NAME}/bedroom.cpp
  src/${PROJECT_NAME}/empty_room.cpp
  fsm/StateMachinePr4.cpp
)

link_directories(
	${PCL_LIBRARY_DIRS}
)
add_definitions(${PCL_DEFINITIONS})

add_executable(nodo_part1 src/nodo_part1.cpp 
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
)

target_link_libraries(nodo_part1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_part1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(nodo_2 src/nodo_2.cpp
  fsm/StateMachinePr4.cpp
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/part2_state_machine.cpp
)

add_executable(nodo_part2 src/nodo_part2.cpp 
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
)
target_link_libraries(nodo_part2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_part2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(nodo_2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


add_executable(nodo_bedroom src/nodo_bedroom.cpp
  src/ejercicio_mapas/bedroom.cpp
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
  src/ejercicio_mapas/part2_state_machine.cpp
  fsm/StateMachinePr4.cpp
)
target_link_libraries(nodo_bedroom ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_bedroom ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


add_executable(nodo_emptyroom src/nodo_emptyroom.cpp
  src/ejercicio_mapas/empty_room.cpp
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
  src/ejercicio_mapas/part2_state_machine.cpp
  fsm/StateMachinePr4.cpp
)
target_link_libraries(nodo_emptyroom ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_emptyroom ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


add_executable(nodo_gym src/nodo_gym.cpp
  src/ejercicio_mapas/gym.cpp
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
  src/ejercicio_mapas/part2_state_machine.cpp
  fsm/StateMachinePr4.cpp
)
target_link_libraries(nodo_gym ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_gym ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


add_executable(nodo_kitchen src/nodo_kitchen.cpp
  src/ejercicio_mapas/kitchen.cpp
  src/ejercicio_mapas/coord_reader.cpp
  src/ejercicio_mapas/movement.cpp
  src/ejercicio_mapas/part2_state_machine.cpp
  fsm/StateMachinePr4.cpp
)
target_link_libraries(nodo_kitchen ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(nodo_kitchen ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

roslint_cpp(

  src/nodo_part1.cpp

  src/nodo_2.cpp
  src/nodo_part2.cpp
  src/nodo_bedroom.cpp
  src/nodo_emptyroom.cpp
  src/nodo_gym.cpp
  src/nodo_kitchen.cpp

  src/ejercicio_mapas/coord_reader.cpp
  include/ejercicio_mapas/coord_reader.hpp

  src/ejercicio_mapas/movement.cpp
  include/ejercicio_mapas/movement.hpp

  src/ejercicio_mapas/part2_state_machine.cpp
  include/ejercicio_mapas/part2_state_machine.hpp

  src/ejercicio_mapas/gym.cpp
  src/ejercicio_mapas/kitchen.cpp
  src/ejercicio_mapas/bedroom.cpp
  src/ejercicio_mapas/empty_room.cpp
  include/ejercicio_mapas/gym.hpp
  include/ejercicio_mapas/kitchen.hpp
  include/ejercicio_mapas/bedroom.hpp
  include/ejercicio_mapas/empty_room.hpp
  
  fsm/StateMachinePr4.cpp
  fsm/StateMachinePr4.h

)