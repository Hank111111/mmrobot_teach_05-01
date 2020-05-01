QT += quick core
CONFIG += c++11
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        list_model_manager.cpp \
        main.cpp \
        name_id_list_model.cpp \
        object_attrib_manager.cpp \
        robot_db_interface.cpp \
        teach_msg_publisher.cpp \
        visual_object.cpp

RESOURCES += qml.qrc
LIBS += -lmysqlcppconn
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH += \
    usr/include
DEPENDPATH += \
    usr/local
HEADERS += \
    list_model_manager.h \
    name_id_list_model.h \
    object_attrib_manager.h \
    robot_db_interface.h \
    table_names_definition.h \
    teach_msg_publisher.h \
    visual_object.h

# ROS related
INCLUDEPATH += /opt/ros/kinetic/include
DEPENDPATH +=   /opt/ros/kinetic/include
INCLUDEPATH += /home/USERNAME/bzrobot_ws/devel/include

DISTFILES += \
    CMakeLists.txt
