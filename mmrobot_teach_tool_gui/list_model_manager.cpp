#include "list_model_manager.h"

EquipTypeListModelManager::EquipTypeListModelManager(QObject *parent)
    :QObject(parent)
{
    current_max_type_id_= 0;
}
void EquipTypeListModelManager::setDBInterface(RobotDBInterface* db_interface_ptr){
    db_interface_ptr_ = db_interface_ptr;
}


bool EquipTypeListModelManager::retrieveFromDB(){

    equip_type_list_model_.beginResetModel();
    equip_type_list_model_.clear();
    map_equip_type_name_to_type_id_.clear();
    current_max_type_id_ = 0;
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    ss_cmd << "SELECT * FROM "<< TABLENAME_EQUIPMENT_TYPE_NAME<<";";
    std::cout<<"sql command :"<<ss_cmd.str()<<std::endl;
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));
    int line_num = 0;
    while(res->next()){
        int type_id = res->getInt("type_id");
        std::string type_name = res->getString("type_name");
        if(type_id > current_max_type_id_) current_max_type_id_ = type_id;
        equip_type_list_model_.addListItem(NameIDElement(type_name, type_id));
        map_equip_type_name_to_type_id_.insert({type_name, type_id});
        line_num ++;
    }
    equip_type_list_model_.endResetModel();
    if(line_num == 0){
        std::cout<<"error: no data can be parsed"<<std::endl;
        return false;
    }
    return true;
}
Q_INVOKABLE int EquipTypeListModelManager::getTypeId(const QString& equip_type_name){
    return map_equip_type_name_to_type_id_.at(equip_type_name.toStdString());
}
bool EquipTypeListModelManager::addToDB(const std::string& equip_type_name){
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    ss_cmd << "INSERT INTO "<< TABLENAME_EQUIPMENT_TYPE_NAME
           << " ( type_name, type_id)"
            << " VALUES ('"<<equip_type_name<<"' , "<<current_max_type_id_+1<<");";
    std::cout<<"ss_cmd: \n"<<ss_cmd.str()<<std::endl;
    bool success = stmt->execute(ss_cmd.str());

    // create equipment_type_*_details table
    std::stringstream drop_if_exist_cmd;
    drop_if_exist_cmd<< "DROP TABLE IF EXISTS `"<<getTableNameEquipmentTypeDetails(current_max_type_id_+1)<<"`;";
    std::cout<<"ss_cmd: \n"<<drop_if_exist_cmd.str()<<std::endl;
    success = success & stmt->execute(drop_if_exist_cmd.str());

    std::string create_table_cmd = getCreateNewEquipTypeTableSqlCmd(current_max_type_id_+1);
    std::cout<<"ss_cmd: "<<create_table_cmd<<std::endl;
    success = success & stmt->execute(create_table_cmd);
    current_max_type_id_ += 1;

    // update from DB
    retrieveFromDB();
    return success;
}
bool EquipTypeListModelManager::addToDB(const QString& equip_type_name){
    std::string equip_type_name_std = equip_type_name.toStdString();
    return addToDB(equip_type_name_std);
}


bool EquipTypeListModelManager::deleteFromDB(int equip_type_id){
    std::cout<<"delete type_id ["<<equip_type_id<<"]from DB is not implemented!"<<std::endl;
    return true;
}

EquipNameListModelManager::EquipNameListModelManager(QObject *parent)
    :QObject(parent)
{
}
void EquipNameListModelManager::setDBInterface(RobotDBInterface* db_interface_ptr){
    db_interface_ptr_ = db_interface_ptr;
}

bool EquipNameListModelManager::retrieveFromDB(int equip_type_id){
    equip_name_list_model_.beginResetModel();
    equip_name_list_model_.clear();
    map_equip_name_to_id_.clear();
    if(equip_type_id < 0){
        equip_type_id = equip_type_id_;
    }
    else
        equip_type_id_ = equip_type_id;

    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    //SELECT id, name FROM equipment
    //WHERE type = 1;
    ss_cmd << "SELECT "<< "id, name FROM "
           <<TABLENAME_EQUIPMENT
            << " WHERE type ="<< equip_type_id <<" ORDER BY id ASC;";
    std::cout<<"sql command :"<<ss_cmd.str()<<std::endl;
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));
    int line_num = 0;
    while(res->next()){
        int equip_id = res->getInt("id");
        std::string equip_name = res->getString("name");
        equip_name_list_model_.addListItem(NameIDElement(equip_name, equip_id));
        map_equip_name_to_id_.insert({equip_name, equip_id});
        line_num ++;
    }
    equip_name_list_model_.endResetModel();

    if(line_num == 0){
        std::cout<<"error: no data can be parsed"<<std::endl;
        return false;
    }
    return true;
}

bool EquipNameListModelManager::addToDB(const std::string& equip_name, const int& type_id){
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    ss_cmd << "INSERT INTO "<< TABLENAME_EQUIPMENT
           << " ( name, type)"
            << " VALUES ('"<<equip_name<<"', "<<type_id<<");";
    std::cout<<"ss_cmd: "<<ss_cmd.str()<<std::endl;

    bool success = stmt->execute(ss_cmd.str());

    // update from DB
    retrieveFromDB(-1);
    return success;
}
bool EquipNameListModelManager::addToDB(const QString& equip_name, const int& type_id){
    std::string equip_name_std = equip_name.toStdString();
    return addToDB(equip_name_std, type_id);
}


bool EquipNameListModelManager::copyVisualObjectsOfEquipment(const int equip_type_id, const int equip_id_copy_from, const int equip_id_copy_to, std::string QRCode_0_content, std::string QRCode_1_content){
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    /*
    DROP TEMPORARY TABLE IF EXISTS tmptable_copy_equip;
    CREATE TEMPORARY TABLE tmptable_copy_equip SELECT * FROM equipment_type_0_details WHERE equipment_id = 1;
    UPDATE tmptable_copy_equip SET equipment_id = 10, id = 0 WHERE equipment_id=1;
    INSERT INTO equipment_type_0_details SELECT * FROM tmptable_copy_equip;
    DROP TEMPORARY TABLE IF EXISTS tmptable_copy_equip;
    */
    bool success = stmt->execute("DROP TEMPORARY TABLE IF EXISTS tmptable_copy_equip;");
    ss_cmd <<"CREATE TEMPORARY TABLE tmptable_copy_equip SELECT * FROM "<<getTableNameEquipmentTypeDetails(equip_type_id)
            <<" WHERE equipment_id = "<<equip_id_copy_from<<";";
    success = success & stmt->execute(ss_cmd.str());

    ss_cmd.str("");
    ss_cmd <<"UPDATE tmptable_copy_equip SET equipment_id = "<<equip_id_copy_to<<", id = 0 WHERE equipment_id ="<<equip_id_copy_from<<";";
    std::cout<<"ss_cmd: "<<ss_cmd.str()<<std::endl;
    success = success & stmt->execute(ss_cmd.str());

    ss_cmd.str("");
    ss_cmd <<"UPDATE tmptable_copy_equip SET additional_text_info = '"<<QRCode_0_content<<"' WHERE equipment_id="<<equip_id_copy_to<< " AND object_unique_id_on_equipment = 0 ;";
    std::cout<<"ss_cmd: "<<ss_cmd.str()<<std::endl;

    success = success & stmt->execute(ss_cmd.str());

    ss_cmd.str("");
    ss_cmd <<"UPDATE tmptable_copy_equip SET additional_text_info = '"<<QRCode_1_content<<"' WHERE equipment_id="<<equip_id_copy_to<< " AND object_unique_id_on_equipment = 1 ;";
    success = success & stmt->execute(ss_cmd.str());

    ss_cmd.str("");
    ss_cmd <<"INSERT INTO "<<getTableNameEquipmentTypeDetails(equip_type_id)<<" SELECT * FROM tmptable_copy_equip;";
    success = success & stmt->execute(ss_cmd.str());

    ss_cmd.str("");
    ss_cmd <<"DROP TEMPORARY TABLE IF EXISTS tmptable_copy_equip;";
    success = success & stmt->execute(ss_cmd.str());

    return success;
}
bool EquipNameListModelManager::copyVisualObjectsOfEquipment(const int equip_type_id, const QString& equip_name_copy_from, const QString& equip_name_copy_to, const QString& QRCode_0_content, const QString& QRCode_1_content){
    int equip_id_copy_from = map_equip_name_to_id_.at(equip_name_copy_from.toStdString());
    int equip_id_copy_to = map_equip_name_to_id_.at(equip_name_copy_to.toStdString());
    return copyVisualObjectsOfEquipment(equip_type_id, equip_id_copy_from, equip_id_copy_to, QRCode_0_content.toStdString(), QRCode_1_content.toStdString());
}

bool EquipNameListModelManager::deleteFromDB(int equip_id){
    std::cout<<"delete type_id ["<<equip_id<<"]from DB is not implemented!"<<std::endl;
    return true;
}
void EquipNameListModelManager::updateListSlot(const int &equip_type_id_msg) {
    std::cout<<"updateListSlot receives equip_type_id_msg: "<<equip_type_id_msg<<std::endl;
    retrieveFromDB(equip_type_id_msg);

}

ObjNameListModelManager::ObjNameListModelManager(QObject *parent)
    :QObject(parent)
{
}

void ObjNameListModelManager::setDBInterface(RobotDBInterface* db_interface_ptr){
    db_interface_ptr_ = db_interface_ptr;
}
bool ObjNameListModelManager::retrieveFromDB(int equip_type_id, int equip_id){
    obj_list_model_.beginResetModel();
    obj_list_model_.clear();
    map_obj_unique_id_to_name_.clear();
    setErrorMsg("");
    if(equip_type_id < 0){
        equip_type_id = equip_type_id_;
        equip_id = equip_id_;
    }
    else{
        equip_type_id_ = equip_type_id;
        equip_id_ = equip_id;
    }

    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    //SELECT equipment_type_1_details.object_unique_id_on_equipment, object_name_on_equipment_type_0.object_type_name
    //FROM Power_distribution_room.object_name_on_equipment_type_0, Power_distribution_room.equipment_type_1_details
    //WHERE equipment_type_1_details.equipment_id=1 AND object_name_on_equipment_type_0.object_type_id = equipment_type_1_details.object_type_id;
    ss_cmd << "SELECT "<<getTableNameEquipmentTypeDetails(equip_type_id_)<<".object_unique_id_on_equipment, "
           << TABLENAME_OBJECT_NAME<<".object_type_name FROM "<<getTableNameEquipmentTypeDetails(equip_type_id_)<<", "<<TABLENAME_OBJECT_NAME
           <<" WHERE "<<getTableNameEquipmentTypeDetails(equip_type_id_)<<".equipment_id="<<equip_id<<" AND "<<getTableNameEquipmentTypeDetails(equip_type_id_)
          <<".object_type_id = "<<TABLENAME_OBJECT_NAME<<".object_type_id ORDER BY object_unique_id_on_equipment ASC;";
    std::cout<<"sql command :"<<ss_cmd.str()<<std::endl;
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));
    int line_num = 0;
    while(res->next()){
        int unique_id = res->getInt("object_unique_id_on_equipment");
        std::string object_name = res->getString("object_type_name");
        obj_list_model_.addListItem(NameIDElement(object_name, unique_id));
        std::string error_msg;
        if(!checkNewObjValid(object_name, unique_id, error_msg)){
            setErrorMsg(error_msg);
            std::cout<<"ERROR: "<<error_msg<<std::endl;
        }
        else{
            map_obj_unique_id_to_name_.insert({unique_id, object_name});
        }
        std::cout<<"add to list: "<<object_name<<", "<<unique_id<<std::endl;
        line_num ++;
    }
    obj_list_model_.endResetModel();
    if(line_num == 0){
        std::cout<<"error: no data can be parsed"<<std::endl;
        return false;
    }
    return true;
}
bool ObjNameListModelManager::retrieveObjTypeIdTypeNameMapFromDB(){
    obj_type_name_id_list_model_.beginResetModel();
    obj_type_name_id_list_model_.clear();
    map_obj_type_id_to_name_.clear();
    map_obj_type_name_to_id_.clear();
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    //SELECT object_type_id, object_type_name FROM Power_distribution_room.object_name_on_equipment_type_0;
    ss_cmd<<"SELECT object_type_id, object_type_name FROM "<<TABLENAME_OBJECT_NAME<<";";
    std::cout<<"sql command :"<<ss_cmd.str()<<std::endl;
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));
    int line_num = 0;
    while(res->next()){
        int obj_type_id = res->getInt("object_type_id");
        std::string object_name = res->getString("object_type_name");
        map_obj_type_id_to_name_.insert({obj_type_id, object_name});
        map_obj_type_name_to_id_.insert({object_name, obj_type_id});
        obj_type_name_id_list_model_.addListItem(NameIDElement(QString::fromStdString(object_name), obj_type_id));
        std::cout<<"add name: "<<object_name<<std::endl;
        line_num ++;
    }
    obj_type_name_id_list_model_.endResetModel();
    if(line_num == 0){
        std::cout<<"error: no data can be parsed"<<std::endl;
        return false;
    }
    return true;

}

bool ObjNameListModelManager::addToDB(int equip_type_id, int equip_id, const std::string& obj_type_name, int obj_unque_id, std::string& error_info){
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    auto obj_type_pair_iter = map_obj_type_name_to_id_.find(obj_type_name);
    if(obj_type_pair_iter == map_obj_type_name_to_id_.end()){
        error_info = "`" + obj_type_name + "' 不是已在数据库中注册的VisualObject类型";
        return false;
    }

    int obj_type_id = obj_type_pair_iter->second;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;
    ss_cmd << "INSERT INTO "<< getTableNameEquipmentTypeDetails(equip_type_id)
           << " ( equipment_id, object_type_id, object_unique_id_on_equipment)"
            << " VALUES ("<<equip_id<<", "<<obj_type_id<<", "<< obj_unque_id<<");";
    bool success = stmt->execute(ss_cmd.str());
    // update from DB
    retrieveFromDB(-1, -1);
    return success;
}
QVariantMap ObjNameListModelManager::addToDB(int equip_type_id, int equip_id, const QString& obj_type_name, int obj_unque_id){
    std::string obj_type_name_std = obj_type_name.toStdString();
    std::string error_info_std;

    bool success = addToDB(equip_type_id, equip_id, obj_type_name_std, obj_unque_id, error_info_std);

    QVariantMap value;
    value.insert("success", success);
    value.insert("error_info", QString::fromStdString(error_info_std));
    return value;
}
void ObjNameListModelManager::updateListSlot(const int &equip_type_id_msg, const int &equip_id_msg){
    if(equip_type_id_msg < 0 || equip_id_msg < 0 ) return;
    std::cout<<"ObjNameListModelManager's updateListSlot receives equip_type_id_msg: "<<equip_type_id_msg<<" , equip_id_msg:"<<equip_id_msg<<std::endl;

    if(map_obj_type_name_to_id_.size() == 0)
        retrieveObjTypeIdTypeNameMapFromDB();
    retrieveFromDB(equip_type_id_msg, equip_id_msg);
}

bool ObjNameListModelManager::checkNewObjValid(const std::string& obj_type_name, const int& obj_unique_id, std::string& error_info){
    // check obj type name exist
    auto obj_type_name_iter = map_obj_type_name_to_id_.find(obj_type_name);
    if(obj_type_name_iter == map_obj_type_name_to_id_.end()){
        error_info = "`" + obj_type_name + "' 不是已在数据库中注册的VisualObject类型";
        return false;
    }

    // check unique id has not been used
    auto obj_unqiue_id_iter = map_obj_unique_id_to_name_.find(obj_unique_id);
    if(obj_unqiue_id_iter != map_obj_unique_id_to_name_.end()){
        error_info = "检测到UniqueID冲突！ UniqueId (" + std::to_string(obj_unique_id) + ") ";
        return false;
    }

    // check unique id for QRCode
    if(obj_unique_id == 0 || obj_unique_id == 1){
        if(obj_type_name != "QRCode"){
            error_info = "UniqueId 为 0 或 1 的VisualObject只能是QRCode";
            return false;
        }
    }
    if(obj_type_name == "QRCode"){
        if(obj_unique_id != 0 && obj_unique_id != 1){
            error_info = "QRCode的UniqueId只能是0或者1";
            return false;
        }
    }
    return true;
}
void ObjNameListModelManager::setErrorMsg(std::string error){
    m_error = QString::fromStdString(error);
    emit onErrorMsgChanged();
}

bool ObjNameListModelManager::checkNewObjValid(const QString& obj_type_name, const int& obj_unique_id){
    std::string error_msg;
    bool success = checkNewObjValid(obj_type_name.toStdString(), obj_unique_id, error_msg);
    setErrorMsg(error_msg);
    return success;
}
