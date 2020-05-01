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
            text: qsTr("关节角示教")
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


            Label{

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter

                anchors.margins: 30
                anchors.topMargin: 50
                width: parent.width - 60
                height: 50
                id:teachGrabDatasetMsg
                text: "- 按下按钮以自动记录关节角"
                wrapMode:Text.Wrap
            }

            Button{
                id: buttonGrabData
                anchors.top: teachGrabDatasetMsg.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50
               
                height: 35
                text: "记录关节角"
                onClicked:{
                    var currentItem = objectUniqueIdCombo.delegateModel.items.get(objectUniqueIdCombo.currentIndex)

                    teachCabinetPosMsgPublisher.publish("ele", equipmentName, currentItem.model.name, equipmentTypeId,currentItem.model.id)
                    console.debug("sent msg to teachCabinetPosMsgPublisher")
                }
            }
            Button{
                id:buttonNext
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 30
                text:"下一步"
                onClicked: stackView.push("qrc:/InitVisualCabinetPage.qml",{ equipmentTypeName: equipmentTypeName, equipmentName: equipmentName,
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






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
