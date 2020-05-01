import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    property string equipmentName: "unknown"
    property string equipmentTypeName: "unknown"

    property int equipmentId: -1
    property int equipmentTypeId: -1

    header: ToolBar {

        ToolButton {
            text: qsTr("上一步")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }
        Label {
            text: qsTr("QRCode示教")
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
                text: "Visual Object"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft


            }
            ComboBox{
                id: objectUniqueIdCombo
                anchors.left: objectUniqueIdLabel.left
                anchors.top: objectUniqueIdLabel.bottom
                anchors.topMargin: 10
                width: 150
                height: objectUniqueIdLabel.height
                textRole: "name_and_id"
                model: objNameModel

            }
            Label{
                anchors.top: objectUniqueIdCombo.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachMsg0
                text: "- 对于 auto_refine=0 的Object，请留意弹出的手动标定框，单击左键依次标记四个角点，双击左键确认，鼠标中键可拖拽角点
- refine完成后，请使用\"rqt_image_view\"可视化\"/mm_visual/wrapper/visualization\"以检查结果"
                wrapMode:Text.Wrap
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
                id: buttonRefine
                anchors.top: buttonMoveToInitCapPose.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 100
                height: 35
                text: "Refine"
                onClicked:{
                    var currentItem = objectUniqueIdCombo.delegateModel.items.get(objectUniqueIdCombo.currentIndex)
                    teachRefineMsgPublisher.publish(equipmentTypeId, equipmentId, currentItem.model.id, currentItem.model.name)
                }
            }

            Label{
                anchors.top: buttonRefine.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachMsg1
                text: "- 请固定底盘并将机械臂移动至相应的Object，确保相机能正确拍摄到后，按下按钮"
                wrapMode:Text.Wrap
            }

            Button{
                id:buttonNext
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 30
                text:"下一步"
                onClicked: stackView.push("qrc:/TeachOffsetPage.qml", 
                                { equipmentTypeName: equipmentTypeName, equipmentName: equipmentName,
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

