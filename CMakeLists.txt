cmake_minimum_required(VERSION 2.8.3)
project(odom_to_tf)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nav_msgs
  tf
)

# add_message_files(
#   FILES
# )

# generate_messages(
#    DEPENDENCIES
#    nav_msgs
#  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package(CATKIN_DEPENDS roscpp nav_msgs tf)

add_executable(odom_to_tf src/odom_to_tf.cpp)
target_link_libraries(odom_to_tf ${catkin_LIBRARIES})
