#ifndef OBJECT_ATTRIB_MANAGER_H
#define OBJECT_ATTRIB_MANAGER_H

#include "visual_object.h"
class ObjectAttribManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool quatValid MEMBER m_quat_valid NOTIFY onQuatValidChanged)
    Q_PROPERTY(int equipId MEMBER m_equipment_id WRITE writeEquipmentId)
    Q_PROPERTY(int equipTypeId MEMBER m_equipment_type_id WRITE writeEquipTypeId)
    Q_PROPERTY(int objUniqueId MEMBER m_obj_unique_id WRITE writeObjUniqueId)
    Q_PROPERTY(double posX MEMBER m_pos_x NOTIFY onPosXChanged)
    Q_PROPERTY(double posY MEMBER m_pos_y NOTIFY onPosYChanged)
    Q_PROPERTY(double posZ MEMBER m_pos_z NOTIFY onPosZChanged)
    Q_PROPERTY(double quatX MEMBER m_q_x NOTIFY onQuatXChanged)
    Q_PROPERTY(double quatY MEMBER m_q_y NOTIFY onQuatYChanged)
    Q_PROPERTY(double quatZ MEMBER m_q_z NOTIFY onQuatZChanged)
    Q_PROPERTY(double quatW MEMBER m_q_w NOTIFY onQuatWChanged)
    Q_PROPERTY(double sizeWidth MEMBER m_width NOTIFY onWidthChanged)
    Q_PROPERTY(double sizeHeight MEMBER m_height NOTIFY onHeightChanged)
    Q_PROPERTY(double bestCapOffsetX MEMBER m_best_cap_offset_x NOTIFY onBestCapOffsetXChanged)
    Q_PROPERTY(double bestCapOffsetY MEMBER m_best_cap_offset_y NOTIFY onBestCapOffsetYChanged)
    Q_PROPERTY(double bestCapOffsetZ MEMBER m_best_cap_offset_z NOTIFY onBestCapOffsetZChanged)
    Q_PROPERTY(QString additionalInfo MEMBER m_additional_info NOTIFY onAdditionalInfoChanged)
    Q_PROPERTY(int canAutoRefine MEMBER m_can_auto_refine NOTIFY onCanAutoRefineChanged)
    Q_PROPERTY(double radius MEMBER m_radius NOTIFY onRadiusChanged)
    Q_PROPERTY(double trunkSquareSize MEMBER m_trunk_square_size NOTIFY onTrunkSquareSizeChanged)
    


public:
    explicit ObjectAttribManager(QObject *parent = nullptr);
    Q_INVOKABLE bool readMembers();
    void setDBInterface(RobotDBInterface* db_interface_ptr);
    Q_INVOKABLE void saveMembers();

    void writeEquipmentId(const int& new_equip_id);
    void writeEquipTypeId(const int& new_equip_type_id);
    void writeObjUniqueId(const int& new_obj_unique_id);
    Q_INVOKABLE void normalizeQuat();

    Q_INVOKABLE void checkQuatValid();

signals:
    void onPosXChanged();
    void onPosYChanged();
    void onPosZChanged();
    void onQuatXChanged();
    void onQuatYChanged();
    void onQuatZChanged();
    void onQuatWChanged();
    void onWidthChanged();
    void onHeightChanged();
    void onBestCapOffsetXChanged();
    void onBestCapOffsetYChanged();
    void onBestCapOffsetZChanged();
    void onAdditionalInfoChanged();
    void onQuatValidChanged();
    void onCanAutoRefineChanged();
    void onRadiusChanged();
    void onTrunkSquareSizeChanged();
private:
    void emitAllProperty();
    VisualObject visual_obj_;
    RobotDBInterface* db_interface_ptr_;
    bool m_quat_valid;

    int m_equipment_id;
    int m_equipment_type_id;
    int m_obj_unique_id;
    double m_pos_x, m_pos_y, m_pos_z;
    double m_q_x, m_q_y, m_q_z, m_q_w;
    double m_width, m_height;
    double m_best_cap_offset_x, m_best_cap_offset_y, m_best_cap_offset_z;
    QString m_additional_info;
    int m_can_auto_refine;
    double m_radius;
    double m_trunk_square_size;
};
#endif // OBJECT_ATTRIB_MANAGER_H
