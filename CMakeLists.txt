cmake_minimum_required(VERSION 3.0.2)
project(gps_node)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES gps_node
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs
  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(gps_node src/gps_main.cpp)

add_dependencies(gps_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(gps_node
  ${catkin_LIBRARIES}
)
