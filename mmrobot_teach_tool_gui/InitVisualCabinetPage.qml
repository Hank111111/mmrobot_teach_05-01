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
            text: qsTr("初始化配电柜")
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
            Button{
                id: buttonMoveToQRCode0
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "移动至QRCode0关节角位置"
                onClicked:{
                    moveArmToVisualObjectPublisher.publish(equipmentTypeId, 0)
                }
            }
            Button{
                id: buttonInitQRCode0
                anchors.top: buttonMoveToQRCode0.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "定位QRCode0"
                onClicked:{
                    visualWrapperRequestPublisher.publish(equipmentTypeId, equipmentId, "QRCode", 0)
                }
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
                id: buttonMoveToQRCode1
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "移动至QRCode1关节角位置"
                onClicked:{
                    moveArmToVisualObjectPublisher.publish(equipmentTypeId, 1)
                }
            }
            Button{
                id: buttonInitQRCode1
                anchors.top: buttonMoveToQRCode1.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
                height: 35
                text: "定位QRCode1"
                onClicked:{
                    visualWrapperRequestPublisher.publish(equipmentTypeId, equipmentId, "QRCode", 1)
                }
            }
            Label{
                anchors.top: buttonInitQRCode1.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachSaveOffsetMsg
                text: "请全程确保底盘未移动
请定位QRCode0后再定位QRCode1
注意观察TeachNode输出"
                wrapMode:Text.Wrap
            }

            Button{
                id:buttonNext
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 30
                text:"下一步"
                onClicked: stackView.push("qrc:/TeachRefinePage.qml",{ equipmentTypeName: equipmentTypeName, equipmentName: equipmentName,
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

