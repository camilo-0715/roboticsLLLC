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
  src/${PROJECT_NAME}/Turn.cpp
  src/${PROJECT_NAME}/BlueGoal.cpp
  src/${PROJECT_NAME}/YellowGoal.cpp
  src/${PROJECT_NAME}/StateMachine.cpp
  src/${PROJECT_NAME}/Ball.cpp
  src/${PROJECT_NAME}/ball_detector.cpp
  src/${PROJECT_NAME}/blueGoal_detector.cpp
  src/${PROJECT_NAME}/yellowGoal_detector.cpp
  
  fsm/StateMachinePr3.cpp
)

link_directories(
	${PCL_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})

add_executable(nodo_p3 src/nodo_p3.cpp
  src/practica3/ball_detector.cpp
  src/practica3/blueGoal_detector.cpp
  src/practica3/yellowGoal_detector.cpp
)
target_link_libraries(nodo_p3 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

# add_executable(nodo_detector_bola src/practica3/ball_detector.cpp)
# add_executable(nodo_detector_pAzul src/practica3/blueGoal_detector.cpp)
# add_executable(nodo_detector_pAmarilla src/practica3/yellowGoal_detector.cpp)

#target_link_libraries(nodo_detector_bola ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
#target_link_libraries(nodo_detector_pAzul ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
#target_link_libraries(nodo_detector_pAmarilla ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(nodo_sm src/nodo_sm.cpp
	src/practica3/StateMachine.cpp
	fsm/StateMachinePr3.cpp)
target_link_libraries(nodo_sm ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(nodo_ball src/nodo_ball.cpp 
  src/practica3/ball_detector.cpp
  src/practica3/Ball.cpp
)
target_link_libraries(nodo_ball ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(nodo_blue src/nodo_blue.cpp 
  src/practica3/blueGoal_detector.cpp
  src/practica3/BlueGoal.cpp
)
target_link_libraries(nodo_blue ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(nodo_yellow src/nodo_yellow.cpp 
  src/practica3/yellowGoal_detector.cpp
  src/practica3/YellowGoal.cpp
)
target_link_libraries(nodo_yellow ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(nodo_turn src/nodo_turn.cpp
  src/practica3/Turn.cpp
)
target_link_libraries(nodo_turn ${catkin_LIBRARIES})



add_dependencies(nodo_p3 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(nodo_ball ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(nodo_turn ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(nodo_yellow ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(nodo_blue ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(nodo_sm ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# add_dependencies(nodo_detector_bola ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# add_dependencies(nodo_detector_pAzul ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# add_dependencies(nodo_detector_pAmarilla ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


roslint_cpp(
  src/nodo_p3.cpp
  
  src/practica3/ball_detector.cpp
  src/practica3/blueGoal_detector.cpp
  src/practica3/yellowGoal_detector.cpp
  
  fsm/StateMachinePr3.cpp
  
  src/nodo_sm.cpp
  src/nodo_ball.cpp
  src/nodo_blue.cpp
  src/nodo_yellow.cpp
  src/nodo_turn.cpp

  src/practica3/Turn.cpp
  src/practica3//BlueGoal.cpp
  src/practica3/YellowGoal.cpp
  src/practica3/StateMachine.cpp
  src/practica3/Ball.cpp
      
  include/practica3/ball_detector.hpp
  include/practica3/blueGoal_detector.hpp
  include/practica3/yellowGoal_detector.hpp
  
  fsm/StateMachinePr3.h

  include/practica3/Turn.hpp
  include/practica3//BlueGoal.hpp
  include/practica3/YellowGoal.hpp
  include/practica3/StateMachine.hpp
  include/practica3/Ball.hpp
  
)
