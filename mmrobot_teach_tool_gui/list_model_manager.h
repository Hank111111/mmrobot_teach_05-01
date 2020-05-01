#ifndef LISTMODELMANAGER_H
#define LISTMODELMANAGER_H

#include <QObject>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "name_id_list_model.h"
#include "visual_object.h"
#include "robot_db_interface.h"
class EquipTypeListModelManager:public QObject
{
    Q_OBJECT
private:
    RobotDBInterface* db_interface_ptr_;
    int current_max_type_id_;
public:
    NameIDListModel equip_type_list_model_;
    std::map<std::string, int> map_equip_type_name_to_type_id_;
public:
    explicit EquipTypeListModelManager(QObject *parent=nullptr);
    void setDBInterface(RobotDBInterface* db_interface_ptr);

    EquipTypeListModelManager(RobotDBInterface* db_interface_ptr);
    Q_INVOKABLE bool retrieveFromDB();
    bool addToDB(const std::string& equip_type_name);
    Q_INVOKABLE bool addToDB(const QString& equip_type_name);
    Q_INVOKABLE int getTypeId(const QString& equip_type_name);

    bool deleteFromDB(int equip_type_id);
};

class EquipNameListModelManager:public QObject{
    Q_OBJECT
private:
    int equip_type_id_;
    RobotDBInterface* db_interface_ptr_;
    std::map<std::string, int> map_equip_name_to_id_;
public:
    NameIDListModel equip_name_list_model_;
public:
    explicit EquipNameListModelManager(QObject *parent=nullptr);
    void setDBInterface(RobotDBInterface* db_interface_ptr);
    bool retrieveFromDB(int equip_type_id);
    bool addToDB(const std::string& equip_name, const int& type_id);
    bool copyVisualObjectsOfEquipment(const int equip_type_id, const int equip_id_copy_from, const int equip_id_copy_to, std::string QRCode_0_content, std::string QRCode_1_content);
    Q_INVOKABLE bool addToDB(const QString& equip_name, const int& type_id);
    Q_INVOKABLE bool copyVisualObjectsOfEquipment(const int equip_type_id, const QString& equip_name_copy_from, const QString& equip_name_copy_to, const QString& QRCode_0_content, const QString& QRCode_1_content);


    bool deleteFromDB(int equip_id);
public slots:
    void updateListSlot(const int &equip_type_id_msg) ;
};


class ObjNameListModelManager:public QObject{
    Q_OBJECT
    Q_PROPERTY(QString errorMsg MEMBER m_error NOTIFY onErrorMsgChanged)

private:
    int equip_type_id_;
    int equip_id_;
    RobotDBInterface* db_interface_ptr_;
    std::map<int, std::string> map_obj_type_id_to_name_;
    std::map<std::string, int> map_obj_type_name_to_id_;
    std::map<int, std::string> map_obj_unique_id_to_name_;
    QString m_error;

    bool checkNewObjValid(const std::string& obj_type_name, const int& obj_unique_id, std::string& error_info);
    void setErrorMsg(std::string error);
public:
    NameIDListModel obj_list_model_;
    NameIDListModel obj_type_name_id_list_model_;
public:
    explicit ObjNameListModelManager(QObject *parent=nullptr);
    void setDBInterface(RobotDBInterface* db_interface_ptr);
    bool retrieveObjTypeIdTypeNameMapFromDB();
    bool retrieveFromDB(int equip_type_id, int equip_id);
    bool addToDB(int equip_type_id, int equip_id, const std::string& obj_type_name, int obj_unque_id, std::string& error_info);
    Q_INVOKABLE QVariantMap addToDB(int equip_type_id, int equip_id, const QString& obj_type_name, int obj_unque_id);
    Q_INVOKABLE bool checkNewObjValid(const QString& obj_type_name, const int& obj_unique_id);
    bool deleteFromDB(int obj_id);
public slots:
    void updateListSlot(const int &equip_type_id_msg, const int &equip_id_msg) ;
signals:
    void onErrorMsgChanged();
};



#endif // LISTMODELMANAGER_H
