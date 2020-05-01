cmake_minimum_required(VERSION 2.8.3)

project(mm_teach_gui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT5_13_PATH /home/data/Qt/5.13.0/gcc_64)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  mm_robot_decision
  message_generation
  roslib
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mm_robot_decision
  CATKIN_DEPENDS message_runtime 
#  DEPENDS system_lib
)

#download qt 5.13.0 and set QT5_13_PATH to the path of it
find_package(Qt5 5.13.0 EXACT  PATHS ${QT5_13_PATH} NO_DEFAULT_PATH COMPONENTS Core Qml Quick )

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)


set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x -fPIC")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} usr/include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
include_directories(${QT5_13_PATH}/include ${QT5_13_PATH}/include/QtGui ${QT5_13_PATH}/include/QtQml ${QT5_13_PATH}/include/QtCore ${QT5_13_PATH}/include/QtQuick)
add_definitions( ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
set(SOURCES
    main.cpp
    list_model_manager.cpp
    name_id_list_model.cpp
    object_attrib_manager.cpp
    robot_db_interface.cpp
    teach_msg_publisher.cpp
    visual_object.cpp
    qml.qrc
)

add_executable(teach_tool ${SOURCES})
add_dependencies(teach_tool mm_robot_decision_generate_messages_cpp)
LINK_DIRECTORIES(${QT5_13_PATH}/lib)

#target_link_libraries(teach_tool Qt5Qml Qt5Gui Qt5Core Qt5Network mysqlcppconn ${catkin_LIBRARIES})

target_link_libraries(teach_tool ${QT5_13_PATH}/lib/libQt5Qml.so.5 ${QT5_13_PATH}/lib/libQt5Gui.so.5 ${QT5_13_PATH}/lib/libQt5Core.so.5 ${QT5_13_PATH}/lib/libQt5Network.so.5 mysqlcppconn ${catkin_LIBRARIES})
# copy all the lld to Qt5_13
# ldd teach_tool | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' Qt5_13/lib
