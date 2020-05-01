import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    header: ToolBar {

        ToolButton {
            text: qsTr("上一步")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }
        Label {
            text: qsTr("配电柜位置示教")
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
                id: comboEquipTypeLabel
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width - 60
                anchors.leftMargin: 50
                anchors.topMargin: 50
                height: 35
                text: "配电柜种类"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft


            }
            ComboBox{
                id:comboEquiTypeCombo
                anchors.left: comboEquipTypeLabel.left
                anchors.top: comboEquipTypeLabel.bottom
                anchors.topMargin: 10
                width: 150
                height: comboEquipTypeLabel.height
                model: equipTypeModel
                textRole: "name"
                onCurrentTextChanged:{
                    equipTypeSignal(equipTypeModelManager.getTypeId(currentText))
                    comboEquipNameCombo.currentIndex = 0
                }

            }

            Label{
                id: comboEquipLabel
                anchors.top: comboEquiTypeCombo.bottom
                anchors.left: comboEquipTypeLabel.left
                anchors.topMargin: 50
                width: parent.width - 60
                height: comboEquipTypeLabel.height
                text: "配电柜ID"
                verticalAlignment: Text.AlignVCenter

            }
            ComboBox{
                id: comboEquipNameCombo
                anchors.left:comboEquipLabel.left
                anchors.top: comboEquipLabel.bottom
                height: comboEquipTypeLabel.height
                anchors.topMargin: 10
                width: 150
                model: equipNameModel
                textRole: "name"
                onCurrentTextChanged: {
                    var currentItem = delegateModel.items.get(currentIndex)
                    console.log("send grab pos signal for id:", currentItem.model.id, "name: ", currentItem.model.name)
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
                id: buttonCabinetPos
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 100
                height: 35
                text: "示教配电柜位置"
                onClicked: {
                    console.log("示教配电柜位置")
                    var currentTypeItem = comboEquiTypeCombo.delegateModel.items.get(comboEquiTypeCombo.currentIndex)
                    var currentNameItem = comboEquipNameCombo.delegateModel.items.get(comboEquipNameCombo.currentIndex)
                    teachCabinetPosMsgPublisher.publish("cab", currentNameItem.model.name, "", currentTypeItem.model.id, -1)
                }
            }
            Label{
                anchors.top: buttonCabinetPos.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 30
                width: parent.width - 60

                id:teachMsg
                text: "请将机器人移动至距离当前配电柜合适的位置后按下‘示教配电柜位置’按钮"
                wrapMode:Text.Wrap
            }


            Button{
                id:buttonNext
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 30
                text:"下一步"
                onClicked: {
                    var currentTypeItem = comboEquiTypeCombo.delegateModel.items.get(comboEquiTypeCombo.currentIndex)
                    var currentNameItem = comboEquipNameCombo.delegateModel.items.get(comboEquipNameCombo.currentIndex)
                    stackView.push("qrc:/TeachJointStatesPage.qml", 
                                { equipmentTypeName: currentTypeItem.model.name, equipmentName: currentNameItem.model.name,
                             equipmentId:currentNameItem.model.id, equipmentTypeId:currentTypeItem.model.id })
                }
            }
        }




    }

    footer: Label{
        id: currentSelectedEquipType
        font.pixelSize: 15
        //text: qsTr("已选择配电柜 类型:") + equipmentTypeName + qsTr(", 名称: ") + equipmentName
    }

}















































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
