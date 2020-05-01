#ifndef TEACH_MSG_PUBLISHER_H
#define TEACH_MSG_PUBLISHER_H

#include "ros/ros.h"

#include <string>
#include "mm_robot_decision/PositionRecord.h"
#include "mm_robot_decision/VisualAppRequest.h"
#include "mm_robot_decision/pose4.h"
#include "std_msgs/Int8.h"
#include "robot_db_interface.h"
#include <QObject>
#include <QString>
#include "table_names_definition.h"
template <typename MsgT>
class TeachMsgPublisherBase{
protected:
    ros::Publisher pub;
public:
    TeachMsgPublisherBase(ros::NodeHandle& n, std::string topic_name){
        pub = n.advertise<MsgT>(topic_name, 10);
    }
};



class TeachCabinetPosMsgPublisher: public QObject, public TeachMsgPublisherBase<mm_robot_decision::PositionRecord>
{
    Q_OBJECT
public:
    TeachCabinetPosMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"/mm_record/order"){
    }
    void publish(std::string type, std::string equip_name, std::string element_name, int equip_type_id, int element_unique_id){
        mm_robot_decision::PositionRecord msg;
        msg.record_type = type; //cab or ele
        msg.equ_name = equip_name;
        msg.ele_name = element_name;
        msg.equ_type = equip_type_id;
        msg.ele_unique_id = element_unique_id;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(QString type, QString equip_name, QString element_name, int equip_type_id, int element_unique_id){
        publish(type.toStdString(), equip_name.toStdString(), element_name.toStdString(), equip_type_id, element_unique_id);
    }
};

class TeachRefineMsgPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    TeachRefineMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/refine_cabinet"){
    }
    void publish(int equip_type, int equip_id, int obj_unique_id, std::string obj_name){
        mm_robot_decision::VisualAppRequest msg;
        msg.object_unique_id_on_equipment = obj_unique_id;
        msg.equipment_id = equip_id;
        msg.equipment_type = equip_type;
        msg.object_name = obj_name;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(int equip_type, int equip_id, int obj_unique_id, QString obj_name){
        publish(equip_type, equip_id, obj_unique_id, obj_name.toStdString());
    }

};


class TeachGrabDataMsgPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    TeachGrabDataMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/grab_data"){
    }
    void publish(int equip_type, int equip_id, std::string obj_name, int obj_unique_id){
        mm_robot_decision::VisualAppRequest msg;
        msg.object_name = obj_name;
        msg.object_unique_id_on_equipment = obj_unique_id;
        msg.equipment_id = equip_id;
        msg.equipment_type = equip_type;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(int equip_type, int equip_id, QString obj_name, int obj_unique_id){
        publish(equip_type, equip_id, obj_name.toStdString(), obj_unique_id);
    }

};

class TeachMoveToPoseWithoutOffsetMsgPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    TeachMoveToPoseWithoutOffsetMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/get_pose_without_offset"){
    }
    void publish(int equip_type, int equip_id, std::string obj_name, int obj_unique_id){
        mm_robot_decision::VisualAppRequest msg;
        msg.object_name = obj_name;
        msg.object_unique_id_on_equipment = obj_unique_id;
        msg.equipment_id = equip_id;
        msg.equipment_type = equip_type;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(int equip_type, int equip_id, QString obj_name, int obj_unique_id){
        publish(equip_type, equip_id, obj_name.toStdString(), obj_unique_id);
    }

};
class TeachSaveCorrectOffsetMsgPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    TeachSaveCorrectOffsetMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/save_correct_offset"){
    }
    void publish(int equip_type, int equip_id, std::string obj_name, int obj_unique_id){
        mm_robot_decision::VisualAppRequest msg;
        msg.object_name = obj_name;
        msg.object_unique_id_on_equipment = obj_unique_id;
        msg.equipment_id = equip_id;
        msg.equipment_type = equip_type;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(int equip_type, int equip_id, QString obj_name, int obj_unique_id){
        publish(equip_type, equip_id, obj_name.toStdString(), obj_unique_id);
    }

};

class ReReadDatabaseMsgPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    ReReadDatabaseMsgPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/re_read_database"){
    }
    Q_INVOKABLE void publish(){
        mm_robot_decision::VisualAppRequest msg;
        pub.publish(msg);
    }
};
class VisualWrapperRequestPublisher:public QObject, public TeachMsgPublisherBase<mm_robot_decision::VisualAppRequest>{
    Q_OBJECT
public:
    VisualWrapperRequestPublisher(ros::NodeHandle& n)
        :TeachMsgPublisherBase(n,"mm_visual/wrapper/request"){
    }
    void publish(int equip_type, int equip_id, std::string obj_name, int obj_unique_id){
        mm_robot_decision::VisualAppRequest msg;
        msg.object_name = obj_name;
        msg.object_unique_id_on_equipment = obj_unique_id;
        msg.equipment_id = equip_id;
        msg.equipment_type = equip_type;
        pub.publish(msg);
    }
    Q_INVOKABLE void publish(int equip_type, int equip_id, QString obj_name, int obj_unique_id){
        publish(equip_type, equip_id, obj_name.toStdString(), obj_unique_id);
    }
};
class MoveArmToVisualObjectPublisher:public QObject, public  TeachMsgPublisherBase<mm_robot_decision::pose4>{
    Q_OBJECT
    Q_PROPERTY(bool arrived MEMBER arrived_ NOTIFY onArrivedChange)
signals:
    void onArrivedChange();
private:
    RobotDBInterface* db_interface_ptr_;
    ros::Subscriber arrive_sub;
    bool arrived_;
public:
    MoveArmToVisualObjectPublisher(ros::NodeHandle& n, RobotDBInterface* db_interface_ptr)
        :TeachMsgPublisherBase(n, "/mm_arm/goal"), db_interface_ptr_(db_interface_ptr)
    {
        arrive_sub = n.subscribe("/mm_arm/isArrived", 5, &MoveArmToVisualObjectPublisher::arriveCallback, this);
    }
    Q_INVOKABLE bool publish(int equip_type, int unique_id){
        // retrive joint angles from database
        std::vector<double> joints_position(6);
        try{
            if(!db_interface_ptr_->checkConnAlive())
                return false;
            std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
            std::stringstream ss_cmd;
            ss_cmd << "SELECT joint1, joint2, joint3, joint4, joint5, joint6 FROM "<< TABLENAME_CAPTURE_POSITION \
            << " WHERE equipment_type="<<equip_type<<" AND element_unique_id="<<unique_id<<";";
            std::cout<<"sql command :"<<ss_cmd.str()<<std::endl;
            std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));
            int line_num = 0;
            
            while(res->next()){
                joints_position[0] = res->getDouble("joint1");
                joints_position[1] = res->getDouble("joint2");
                joints_position[2] = res->getDouble("joint3");
                joints_position[3] = res->getDouble("joint4");
                joints_position[4] = res->getDouble("joint5");
                joints_position[5] = res->getDouble("joint6");
                line_num ++;
            }
            if(line_num > 1){
                std::cout<<"ERROR: you have multiple record with equipment_type="<<equip_type<<" AND element_unique_id="<<unique_id<<std::endl;
                return false;
            }
            if(line_num == 0){
                std::cout<<"ERROR: got nothing from DB!"<<std::endl;
                return false;
            }
        }
        catch(std::exception & e){
            std::cout << e.what() << std::endl;
            return false;
        }
        mm_robot_decision::pose4 arm_goal;
        arm_goal.state="jointSpacePlanning";
        arm_goal.x=joints_position[0];
        arm_goal.y=joints_position[1];
        arm_goal.z=joints_position[2];      
        arm_goal.a=joints_position[3];
        arm_goal.b=joints_position[4];
        arm_goal.c=joints_position[5];
        arm_goal.w=joints_position[6];

        arrived_ = false;
        pub.publish(arm_goal);
        return true;
    }

    void arriveCallback(const std_msgs::Int8::ConstPtr& msg){
        if(arrived_ == false){
            arrived_ = true;
            emit onArrivedChange();
        }
    }

};










#endif // TEACH_MSG_PUBLISHER_H
