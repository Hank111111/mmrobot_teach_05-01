#ifndef VISUAL_OBJECT_H
#define VISUAL_OBJECT_H


#include <eigen3/Eigen/Dense>
#include <memory>
#include "mysql_connection.h"
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "table_names_definition.h"
#include "robot_db_interface.h"
#include <QObject>
class VisualObject{
public:

    int equipment_id;
    int equipment_type_id;

    Eigen::Vector3d pos;
    Eigen::Quaterniond q; // in presented_frame's coordinate

    double width; // in millimeter
    double height;// in millimeter

    Eigen::Vector3d translate_from_obj_to_best_capture_point; //in millimeter
    Eigen::Vector3d result_offset_translate_mm; // in millimeter (directly add to the result)
    Eigen::Vector3d result_offset_euler_deg; // in deg

    std::string object_name; // the Type of visual object, can be `knifeSwitch`, `remoteSwitch`,`handcartSwitch`,`pointMeter`,or `light`
    std::string additional_text_info; // stores the additional infomation, e.g. for qr code, it store the qr code's content
    std::vector<double> additional_numerical_info;
    double radius;  // used for handcart
    double trunk_square_size; //used for handcart
    int object_type_id;
    int object_unique_id_on_equipment; // to identify the objects (even they are the same type) on the same equipment
    bool can_auto_refine;

    
    VisualObject();
    VisualObject(int equipment_id_input, int equipment_type_id_input);
    bool parseSqlResult(std::unique_ptr< sql::ResultSet >& res);
    void updateToSqlDB(std::unique_ptr<sql::Connection>& con);
};



#endif // VISUAL_OBJECT_H
