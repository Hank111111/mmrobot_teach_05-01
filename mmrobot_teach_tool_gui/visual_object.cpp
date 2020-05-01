#include "visual_object.h"

VisualObject::VisualObject(int equipment_id_input, int equipment_type_id_input)
{
    equipment_id = equipment_id_input;
    equipment_type_id = equipment_type_id_input;
    pos.setZero();
    q = Eigen::Quaterniond(1,0,0,0);
    width = 0.0;
    height = 0.0;
    translate_from_obj_to_best_capture_point.setZero();
    result_offset_translate_mm.setZero();
    result_offset_euler_deg.setZero();
    radius=0.0;
    object_type_id = -1;
    object_unique_id_on_equipment = -1;
    can_auto_refine = false;
    trunk_square_size = 0.0;
}

VisualObject::VisualObject(){
    equipment_id = -1;
    equipment_type_id = -1;
    pos.setZero();
    q = Eigen::Quaterniond(1,0,0,0);
    width = 0.0;
    height = 0.0;
    translate_from_obj_to_best_capture_point.setZero();
    result_offset_translate_mm.setZero();
    result_offset_euler_deg.setZero();
    radius=0.0;
    object_type_id = -1;
    object_unique_id_on_equipment = -1;
    can_auto_refine = false;
    trunk_square_size = 0.0;
}
bool VisualObject::parseSqlResult(std::unique_ptr< sql::ResultSet >& res){
    int return_size = 0;
    while(res->next()){

        // parse cabinet name
        //cabinet_name = res->getString("name");

        // parse type
        std::string object_type_name = res->getString("object_type_name");
        object_name = object_type_name;

        object_type_id = res->getInt("object_type_id");
        object_unique_id_on_equipment = res->getInt("object_unique_id_on_equipment");
        // parse pose
        pos(0) = res->getDouble("x");
        pos(1) = res->getDouble("y");
        pos(2) = res->getDouble("z");

        q.x() = res->getDouble("q_x");
        q.y() = res->getDouble("q_y");
        q.z() = res->getDouble("q_z");
        q.w() = res->getDouble("q_w");

        if(fabs(q.norm() - 1.0) < 1e-5)
                std::cout<<"ERROR: the quaternion read sql is not normalized, thus normalize it right now!"<<std::endl;

        q.normalized();

        // parse width and height
        width = res->getDouble("width");
        height = res->getDouble("height");

        // parse dist_to_endeffector_for_capture
        translate_from_obj_to_best_capture_point(0) = res->getDouble("x_from_obj_to_best_capture_point");
        translate_from_obj_to_best_capture_point(1) = res->getDouble("y_from_obj_to_best_capture_point");
        translate_from_obj_to_best_capture_point(2) = res->getDouble("z_from_obj_to_best_capture_point");

        // parse the  offset
        result_offset_euler_deg(0) = res->getDouble("result_offset_euler_x_deg");
        result_offset_euler_deg(1) = res->getDouble("result_offset_euler_y_deg");
        result_offset_euler_deg(2) = res->getDouble("result_offset_euler_z_deg");
        result_offset_translate_mm(0) = res->getDouble("result_offset_x_mm");
        result_offset_translate_mm(1) = res->getDouble("result_offset_y_mm");
        result_offset_translate_mm(2) = res->getDouble("result_offset_z_mm");

        can_auto_refine = res->getBoolean("can_auto_refine");
        // parse the addition_string_info
        additional_text_info = res->getString("additional_text_info");
        std::cout<<"read additional_text_info: "<<additional_text_info<<std::endl;
        // parse the radius and trunk_square_size
        radius = res->getDouble("radius");
        trunk_square_size = res->getDouble("trunk_square_size");
        return_size ++;
    }
    if(return_size > 1){
        std::cout<<"ERROR: got more than one result from DB!"<<std::endl;
        return false;
    }
    if(return_size == 0){
        std::cout<<"ERROR: got nothing from DB!"<<std::endl;
        return false;
    }
    return true;
}

void VisualObject::updateToSqlDB(std::unique_ptr<sql::Connection>& con){
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::string table_name = getTableNameEquipmentTypeDetails(equipment_type_id);
    std::stringstream ss_cmd;
    ss_cmd << "UPDATE "<<table_name
        << " SET x="<<pos(0)<<", y="<<pos(1)<<", z="<<pos(2)
        <<", q_x="<<q.x()<<", q_y="<<q.y()<<", q_z="<<q.z()<<", q_w="<<q.w()
        <<", width="<<width <<", height="<<height

        <<", x_from_obj_to_best_capture_point="<<translate_from_obj_to_best_capture_point(0)
        <<", y_from_obj_to_best_capture_point="<<translate_from_obj_to_best_capture_point(1)
        <<", z_from_obj_to_best_capture_point="<<translate_from_obj_to_best_capture_point(2)
        <<", additional_text_info='"<<additional_text_info<<"'"
        <<", radius="<<radius
        <<", trunk_square_size="<<trunk_square_size
        <<", can_auto_refine="<<static_cast<int>(can_auto_refine)

        << " WHERE equipment_id = "<<equipment_id<<" AND object_type_id = "<<object_type_id<<" AND object_unique_id_on_equipment = " <<object_unique_id_on_equipment<<";";
    std::cout<<"ss_cmd: "<<ss_cmd.str()<<std::endl;
    stmt->executeUpdate(ss_cmd.str());
}

