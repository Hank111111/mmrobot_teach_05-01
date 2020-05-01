#include "object_attrib_manager.h"
ObjectAttribManager::ObjectAttribManager(QObject *parent):QObject(parent){
    m_equipment_id = -1;
    m_equipment_type_id = -1;
    m_obj_unique_id = -1;
}


void ObjectAttribManager::setDBInterface(RobotDBInterface* db_interface_ptr){
    db_interface_ptr_ = db_interface_ptr;
}
void ObjectAttribManager::writeEquipmentId(const int& new_equip_id){
    std::cout<<"new_equip_id: "<<new_equip_id<<std::endl;
    m_equipment_id = new_equip_id;
    readMembers();
}
void ObjectAttribManager::writeEquipTypeId(const int& new_equip_type_id){
    std::cout<<"new_equip_type_id: "<<new_equip_type_id<<std::endl;

    m_equipment_type_id = new_equip_type_id;
    readMembers();
}
void ObjectAttribManager::writeObjUniqueId(const int& new_obj_unique_id){
    std::cout<<"new_obj_unique_id: "<<new_obj_unique_id<<std::endl;

    m_obj_unique_id = new_obj_unique_id;
    readMembers();

}

bool ObjectAttribManager::readMembers(){
    if(m_equipment_id < 0 || m_equipment_type_id < 0 || m_obj_unique_id < 0) return false;
    visual_obj_ = VisualObject(m_equipment_id, m_equipment_type_id);
    if(!db_interface_ptr_->checkConnAlive())
        return false;
    std::unique_ptr<sql::Statement> stmt(db_interface_ptr_->con->createStatement());
    std::stringstream ss_cmd;

    ss_cmd<<"SELECT "<<getTableNameEquipmentTypeDetails(m_equipment_type_id)<<".* , "<< TABLENAME_OBJECT_NAME<<".object_type_name"
         <<" FROM "<<getTableNameEquipmentTypeDetails(m_equipment_type_id)<<" , "<<TABLENAME_OBJECT_NAME
        <<" WHERE equipment_id ="<<m_equipment_id<<" AND object_unique_id_on_equipment="<<m_obj_unique_id
       <<" AND "<<getTableNameEquipmentTypeDetails(m_equipment_type_id)<<".object_type_id = "<< TABLENAME_OBJECT_NAME<<".object_type_id;";
    std::cout<<"ss_cmd: "<<ss_cmd.str()<<std::endl;
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(ss_cmd.str()));

    visual_obj_.parseSqlResult(res);

    m_pos_x = visual_obj_.pos(0);
    m_pos_y = visual_obj_.pos(1);
    m_pos_z = visual_obj_.pos(2);

    m_q_x = visual_obj_.q.x();
    m_q_y = visual_obj_.q.y();
    m_q_z = visual_obj_.q.z();
    m_q_w = visual_obj_.q.w();

    m_width = visual_obj_.width;
    m_height = visual_obj_.height;

    m_can_auto_refine = visual_obj_.can_auto_refine;
    m_radius = visual_obj_.radius;
    m_trunk_square_size = visual_obj_.trunk_square_size;

    m_best_cap_offset_x = visual_obj_.translate_from_obj_to_best_capture_point(0);
    m_best_cap_offset_y = visual_obj_.translate_from_obj_to_best_capture_point(1);
    m_best_cap_offset_z = visual_obj_.translate_from_obj_to_best_capture_point(2);
    m_additional_info = QString::fromStdString(visual_obj_.additional_text_info);
    std::cout<<"m_additional_info: "<<m_additional_info.toStdString()<<std::endl;
    checkQuatValid();
    emitAllProperty();
    return true;

}
void ObjectAttribManager::checkQuatValid(){
    if(fabs(m_q_x * m_q_x + m_q_y*m_q_y + m_q_z*m_q_z + m_q_w*m_q_w - 1.0) > 1e-5){
        std::cout<<"Quaternion is not valid!"<<std::endl;
        m_quat_valid = false;
    }
    else {
        m_quat_valid = true;
    }
    std::cout<<"m_q_x: "<<m_q_x
            <<", m_q_y: "<<m_q_y
            <<", m_q_z: "<<m_q_z
            <<", m_q_w: "<<m_q_w<<std::endl;

    std::cout<<"check quat: "<<m_quat_valid<<std::endl;
    emit onQuatValidChanged();
}
void ObjectAttribManager::normalizeQuat(){
    double norm = sqrt(m_q_x * m_q_x + m_q_y*m_q_y + m_q_z*m_q_z + m_q_w*m_q_w);
    m_q_x /= norm;
    m_q_y /= norm;
    m_q_z /= norm;
    m_q_w /= norm;
    checkQuatValid();
    emit onQuatXChanged();
    emit onQuatYChanged();
    emit onQuatZChanged();
    emit onQuatWChanged();

}
void ObjectAttribManager::emitAllProperty(){
    emit onPosXChanged();
    emit onPosYChanged();
    emit onPosZChanged();
    emit onQuatXChanged();
    emit onQuatYChanged();
    emit onQuatZChanged();
    emit onQuatWChanged();
    emit onWidthChanged();
    emit onHeightChanged();
    emit onBestCapOffsetXChanged();
    emit onBestCapOffsetYChanged();
    emit onBestCapOffsetZChanged();
    emit onAdditionalInfoChanged();
    emit onQuatValidChanged();
    emit onCanAutoRefineChanged();
    emit onRadiusChanged();
    emit onTrunkSquareSizeChanged();

}
void ObjectAttribManager::saveMembers(){

    visual_obj_.pos(0) = m_pos_x;
    visual_obj_.pos(1) = m_pos_y;
    visual_obj_.pos(2) = m_pos_z;

    visual_obj_.q.x() = m_q_x;
    visual_obj_.q.y() = m_q_y;
    visual_obj_.q.z() = m_q_z;
    visual_obj_.q.w() = m_q_w;

    visual_obj_.width = m_width;
    visual_obj_.height = m_height;

    visual_obj_.translate_from_obj_to_best_capture_point(0) = m_best_cap_offset_x;
    visual_obj_.translate_from_obj_to_best_capture_point(1) = m_best_cap_offset_y;
    visual_obj_.translate_from_obj_to_best_capture_point(2) = m_best_cap_offset_z;

    visual_obj_.can_auto_refine = m_can_auto_refine;
    visual_obj_.radius = m_radius;
    visual_obj_.trunk_square_size = m_trunk_square_size;

    visual_obj_.additional_text_info = m_additional_info.toStdString();
    std::cout<<"addtional_text_info: "<<visual_obj_.additional_text_info<<std::endl;
    std::cout<<"Saved params for visual object"<<std::endl;

    visual_obj_.updateToSqlDB(db_interface_ptr_->con);
}

