import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    
    property string equipmentName: "unknown"
    property string equipmentTypeName: "unknown"

    property int equipmentId: -1
    property int equipmentTypeId: -1
    onEquipmentIdChanged:equipIdSignal(equipmentTypeId, equipmentId)
    onEquipmentTypeIdChanged:equipIdSignal(equipmentTypeId, equipmentId)
    header: ToolBar {

        ToolButton {
            text: qsTr("上一步")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }
        Label {
            text: qsTr("Offset示教")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
    RowLayout {
        spacing: 10
        anchors.fill: parent

        Rectangle{
            color: 'lightcyan'
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 150
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            anchors.margins: 30
            id: leftColorColum
            Label{
                id: objectUniqueIdLabel
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width - 60
                anchors.leftMargin: 50
                anchors.topMargin: 50
                height: 35
                text: "Visual Object and UniqueID"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft


            }
            ComboBox{
                id:objectUniqueIdCombo
                anchors.left: objectUniqueIdLabel.left
                anchors.top: objectUniqueIdLabel.bottom
                anchors.topMargin: 10
                width: 180
                height: objectUniqueIdLabel.height
                textRole: "name_and_id"
                model: objNameModel

            }

        }

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 150
            Layout.minimumHeight: 150
            anchors.margins: 30
            Button{
                id: buttonMoveToInitCapPose
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "移动至拍摄关节角"
                onClicked:{
                    var currentItem = objectUniqueIdCombo.delegateModel.items.get(objectUniqueIdCombo.currentIndex)
                    moveArmToVisualObjectPublisher.publish(equipmentTypeId, currentItem.model.id)
                    console.log("use moveArmToVisualObjectPublisher")
                }
            }

            Button{
                id: buttonMoveToPosWithoutOffset
                anchors.top: buttonMoveToInitCapPose.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "移动至初始位置"
                onClicked:{
                    var currentItem = objectUniqueIdCombo.delegateModel.items.get(objectUniqueIdCombo.currentIndex)

                    teachMoveToPoseWithoutOffsetMsgPublisher.publish(equipmentTypeId, equipmentId, currentItem.model.name, currentItem.model.id)
                    console.log("send teachMoveToPoseWithoutOffsetMsg")
                }
            }
            Label{
                anchors.top: buttonMoveToPosWithoutOffset.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachMoveToPosWithoutOffseMsg
                text: "机械臂移动完毕后再手动移动机械臂至准确位置,移动完毕后再按下”保存offset“"
                wrapMode:Text.Wrap
            }
            Button{
                id: buttonSaveOffset
                anchors.top: buttonMoveToPosWithoutOffset.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 100
                height: 35
                text: "保存offset"
                onClicked:{
                    var currentItem = objectUniqueIdCombo.delegateModel.items.get(objectUniqueIdCombo.currentIndex)

                    teachSaveCorrectOffsetMsgPublisher.publish(equipmentTypeId, equipmentId, currentItem.model.name, currentItem.model.id)
                    console.log("send teachSaveCorrectOffsetMsgPublisher")
                }
            }
            Label{
                anchors.top: buttonSaveOffset.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachSaveOffsetMsg
                text: "请全程确保底盘未移动
注意观察TeachNode输出"
                wrapMode:Text.Wrap
            }

            Button{
                id:buttonNext
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 30
                text:"下一步"
                onClicked: stackView.push("qrc:/TeachGrabDataset.qml",{ equipmentTypeName: equipmentTypeName, equipmentName: equipmentName,
                             equipmentId:equipmentId, equipmentTypeId:equipmentTypeId})

            }
        }
    }
    footer: Label{
        id: currentSelectedEquipType
        font.pixelSize: 15
        text: qsTr("已选择配电柜 类型:") + equipmentTypeName + qsTr(", 名称: ") + equipmentName
    }

}

