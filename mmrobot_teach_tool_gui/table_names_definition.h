#ifndef TABLE_NAMES_DEFINITION_H
#define TABLE_NAMES_DEFINITION_H

#include <string>
#include <sstream>
#define TABLENAME_EQUIPMENT_TYPE_NAME "equipment_type_name"
#define TABLENAME_OBJECT_NAME "object_name_on_equipment"
#define TABLENAME_EQUIPMENT "equipment"
#define TABLENAME_CAPTURE_POSITION "capture_position"
inline std::string  getTableNameEquipmentTypeDetails(int type_id){
    return "equipment_type_" + std::to_string(type_id) + "_details";
}
inline std::string getConstraintNameEquipmentTypeDetails(int type_id, int constraint_id){
    return "equipment_type_" + std::to_string(type_id) + "_details_ibfk_" + std::to_string(constraint_id);
}

inline std::string getCreateNewEquipTypeTableSqlCmd(int type_id){
    std::stringstream ss_cmd;
    ss_cmd<< "CREATE TABLE `"<<getTableNameEquipmentTypeDetails(type_id)<<"` (\n\
    `id` int(11) NOT NULL AUTO_INCREMENT,\n\
    `equipment_id` int(11) NOT NULL,\n\
    `object_type_id` int(11) NOT NULL,\n\
    `object_unique_id_on_equipment` int(11) NOT NULL,\n\
    `x` double NOT NULL DEFAULT '0',\n\
    `y` double NOT NULL DEFAULT '0',\n\
    `z` double NOT NULL DEFAULT '0',\n\
    `q_x` double NOT NULL DEFAULT '0',\n\
    `q_y` double NOT NULL DEFAULT '0',\n\
    `q_z` double NOT NULL DEFAULT '0',\n\
    `q_w` double NOT NULL DEFAULT '1',\n\
    `width` double NOT NULL DEFAULT '0',\n\
    `height` double NOT NULL DEFAULT '0',\n\
    `x_from_obj_to_best_capture_point` double NOT NULL DEFAULT '0',\n\
    `y_from_obj_to_best_capture_point` double NOT NULL DEFAULT '100',\n\
    `z_from_obj_to_best_capture_point` double NOT NULL DEFAULT '-500',\n\
    `result_offset_x_mm` double NOT NULL DEFAULT '0',\n\
    `result_offset_y_mm` double NOT NULL DEFAULT '0',\n\
    `result_offset_z_mm` double NOT NULL DEFAULT '0',\n\
    `result_offset_euler_x_deg` double NOT NULL DEFAULT '0',\n\
    `result_offset_euler_y_deg` double NOT NULL DEFAULT '0',\n\
    `result_offset_euler_z_deg` double NOT NULL DEFAULT '0',\n\
    `additional_text_info` varchar(255) COLLATE utf8_bin DEFAULT NULL,\n\
    `can_auto_refine` tinyint(1) NOT NULL DEFAULT '1',\n\
    `radius` double DEFAULT '0',\n\
    `trunk_square_size` double DEFAULT '0',\n\
    PRIMARY KEY (`id`),\n\
    KEY `equipment_id` (`equipment_id`),\n\
    KEY `object_type_id` (`object_type_id`),\n\
    CONSTRAINT `"<<getConstraintNameEquipmentTypeDetails(type_id,0)<<"` FOREIGN KEY (`equipment_id`) REFERENCES `equipment` (`id`),\n\
    CONSTRAINT `"<<getConstraintNameEquipmentTypeDetails(type_id,1)<<"` FOREIGN KEY (`object_type_id`) REFERENCES `"<<TABLENAME_OBJECT_NAME<<"` (`object_type_id`)\n\
); ";
    return ss_cmd.str();
}


#endif // TABLE_NAMES_DEFINITION_H
