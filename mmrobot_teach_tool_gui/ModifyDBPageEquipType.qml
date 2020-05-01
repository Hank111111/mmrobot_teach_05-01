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
            text: qsTr("选择配电柜种类")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }


    RowLayout {
        spacing: 10
        anchors.fill: parent
        TwoColListView {
            id: twoColListViewRoot
            implementedModel:equipTypeModel
            headerName1: "TypeName"
            headerName2: "TypeID"
            roleName1:"name"
            roleName2:"id"
            function sendToNextPage(viewId, data) {
                viewId.push("qrc:/ModifyDBPageEquipName.qml", { equipmentTypeName: data["name"], equipmentTypeId: data["id"] })
            }
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            TextField {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 100
                anchors.top: parent.top
                id: newEquipTypeNameInput
                placeholderText: qsTr("新建配电柜种类")
            }
            Button{
                id: newEquipTypeButton
                anchors.top: newEquipTypeNameInput.bottom
                anchors.topMargin: 20
                anchors.right: newEquipTypeNameInput.right
                text: qsTr("新建")
                onClicked: {

                    if(newEquipTypeNameInput.text === ""){
                        console.log("The input 'newEquipTypeName' is empty!")
                        return
                    }
                    equipTypeModelManager.addToDB(newEquipTypeNameInput.text)
                }
            }

        }
    }
}

































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
