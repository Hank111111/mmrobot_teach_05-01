import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    property string equipmentTypeName: "unknown"
    property string equipmentName: "unknown"
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
            text: qsTr("选择配电柜元件")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }


    RowLayout {
        spacing: 10
        anchors.fill: parent
        TwoColListView {
            id: objNameListView
            implementedModel: objNameModel
            headerName1: "ObjName"
            headerName2: "ObjUniqueID"
            roleName1:"name"
            roleName2:"id"
            function sendToNextPage(viewId, data) {
                viewId.push("qrc:/ModifyDBPageEquipObjectAttrib.qml", { equipmentTypeName: equipmentTypeName, equipmentName: equipmentName,
                                                                visualObjName:data["name"], objectUniqueId:data["id"], equipmentId:equipmentId, equipmentTypeId:equipmentTypeId })
            }
        }




        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            Item {
                id: newObjTypeItem
                anchors.topMargin: 50
                anchors.top: parent.top
                height: 30
                Label{
                    id: newObjTypeLable
                    text: "ObjectType"
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                    width: 50
                    anchors.verticalCenter: parent.verticalCenter
                }
                ComboBox {
                    id:objTypeSelector
                    anchors.left: newObjTypeLable.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 40

                    editable: false
                    textRole: "name"
                    model: objTypeNameIdModel
                }
            }


            TextField {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 20
                anchors.top: newObjTypeItem.bottom
                id: newEquipObjUniqueIdInput
                placeholderText: qsTr("新建配电柜元件UniqueId")
                validator: IntValidator {}
                inputMethodHints: Qt.ImhNoPredictiveText
                selectByMouse: true
                onFocusChanged: {
                    focus ? selectAll() : deselect()
                }
                selectionColor:"gray"
                selectedTextColor:"white"
            }
            Button{
                id: newEquipObjButton
                anchors.top: newEquipObjUniqueIdInput.bottom
                anchors.topMargin: 20
                anchors.right: newEquipObjUniqueIdInput.right
                text: qsTr("新建")
                onClicked: {
                    var checkValid = objNameModelManager.checkNewObjValid(objTypeSelector.currentText, newEquipObjUniqueIdInput.text);
                    if(checkValid){
                        var result = objNameModelManager.addToDB(equipmentTypeId, equipmentId, objTypeSelector.currentText, newEquipObjUniqueIdInput.text);

                        if(!result.success){
                            console.log("errorinfo: ", result.error_info);
                        }
                        else{
                            objNameModelManager.errorMsg = ""
                            console.log("errorMsg: ", objNameModelManager.errorMsg);
                        }
                    }
                    else console.log("checkvalid: ", objNameModelManager.errorMsg)
                }
            }
            Label{
                id:errorMsgText
                anchors.top: newEquipObjButton.bottom
                anchors.topMargin: 20
                anchors.left: newEquipObjUniqueIdInput.left
                anchors.right: newEquipObjButton.right
                height: 100

                text:objNameModelManager.errorMsg
                color: "red"
                wrapMode:Text.Wrap


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
