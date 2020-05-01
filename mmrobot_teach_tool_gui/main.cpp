#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QFont>
#include <QFontDatabase>
#include "name_id_list_model.h"
#include "list_model_manager.h"
#include "object_attrib_manager.h"
#include "teach_msg_publisher.h"
#include "ros/ros.h"
#include <ros/package.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // set font
    std::string path = ros::package::getPath("mm_teach_gui");
    std::cout<<"path: "<<path<<std::endl; 
    int fontId = QFontDatabase::addApplicationFont(QString::fromStdString(path + "/SourceHanSans-Regular.ttf"));
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont f(msyh);
    f.setPointSize(11);
    f.setWeight(QFont::Normal);
    app.setFont(f);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    
    QQmlContext* context = engine.rootContext();


    // ros related
    ros::init(argc, argv, "mm_teach_gui_node");
    ros::NodeHandle nh;
    TeachCabinetPosMsgPublisher teach_cabinet_pose_msg_publisher(nh);
    context->setContextProperty("teachCabinetPosMsgPublisher", &teach_cabinet_pose_msg_publisher);
    
    TeachRefineMsgPublisher teach_refine_msg_publisher(nh);
    context->setContextProperty("teachRefineMsgPublisher", &teach_refine_msg_publisher);
    
    TeachGrabDataMsgPublisher teach_grab_data_msg_publisher(nh);
    context->setContextProperty("teachGrabDataMsgPublisher", &teach_grab_data_msg_publisher);
    
    TeachMoveToPoseWithoutOffsetMsgPublisher teach_move_to_pose_without_offset_msg_publisher(nh);
    context->setContextProperty("teachMoveToPoseWithoutOffsetMsgPublisher", &teach_move_to_pose_without_offset_msg_publisher);

    TeachSaveCorrectOffsetMsgPublisher teach_save_correct_offset_msg_publisher(nh);
    context->setContextProperty("teachSaveCorrectOffsetMsgPublisher", &teach_save_correct_offset_msg_publisher);

    ReReadDatabaseMsgPublisher re_read_database_msg_publisher(nh);
    context->setContextProperty("reReadDatabaseMsgPublisher", &re_read_database_msg_publisher);

    VisualWrapperRequestPublisher visual_wrapper_request_publisher(nh);
    context->setContextProperty("visualWrapperRequestPublisher", &visual_wrapper_request_publisher);



    RobotDBInterface db_interface;
    context->setContextProperty("DBInterface", &db_interface);
    // debug...
    //db_interface.establishSQLConnImpl("127.0.0.1", "mrobot", "123456", "Power_distribution_room");

    MoveArmToVisualObjectPublisher move_arm_to_visual_object_publisher(nh, &db_interface);
    context->setContextProperty("moveArmToVisualObjectPublisher", &move_arm_to_visual_object_publisher);


    EquipTypeListModelManager equip_type_manager;
    equip_type_manager.setDBInterface(&db_interface);

    // debug...
    //equip_type_manager.retrieveFromDB(); //need to be trrigered from cpp or qml in the beginning

    context->setContextProperty("equipTypeModel", &equip_type_manager.equip_type_list_model_);
    context->setContextProperty("equipTypeModelManager", &equip_type_manager);

    EquipNameListModelManager equip_name_manager;
    equip_name_manager.setDBInterface(&db_interface);
    context->setContextProperty("equipNameModel", &equip_name_manager.equip_name_list_model_);
    context->setContextProperty("equipNameModelManager", &equip_name_manager);

    EquipNameListModelManager equip_name_for_copy_manager;
    equip_name_for_copy_manager.setDBInterface(&db_interface);
    context->setContextProperty("equipNameForCopyModel", &equip_name_for_copy_manager.equip_name_list_model_);

    ObjNameListModelManager obj_on_equip_manager;
    obj_on_equip_manager.setDBInterface(&db_interface);
    context->setContextProperty("objNameModel", &obj_on_equip_manager.obj_list_model_);
    context->setContextProperty("objTypeNameIdModel", &obj_on_equip_manager.obj_type_name_id_list_model_);
    context->setContextProperty("objNameModelManager", &obj_on_equip_manager);

    ObjectAttribManager obj_attrib_manager;
    obj_attrib_manager.setDBInterface(&db_interface);
    context->setContextProperty("objAttribs", &obj_attrib_manager);

    engine.load(url);
    QObject *root = engine.rootObjects()[0];
    QObject::connect(root, SIGNAL(equipTypeSignal(int)),
                         &equip_name_manager, SLOT(updateListSlot(int)));

    QObject::connect(root, SIGNAL(equipTypeForCopySignal(int)),
                         &equip_name_for_copy_manager, SLOT(updateListSlot(int)));

    QObject::connect(root, SIGNAL(equipIdSignal(int, int)),
                         &obj_on_equip_manager, SLOT(updateListSlot(int, int)));

    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    return app.exec();
}
