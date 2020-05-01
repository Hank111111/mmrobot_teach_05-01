import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    property string equipmentTypeName:"unknown"
    property int equipmentTypeId: -1
    onEquipmentTypeIdChanged: equipTypeSignal(equipmentTypeId)


    header: ToolBar {

        ToolButton {
            text: qsTr("上一步")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }
        Label {
            text: qsTr("选择配电柜名称")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }


    RowLayout {
        spacing: 10
        anchors.fill: parent
        TwoColListView {
            id:equipNameListView
            implementedModel:equipNameModel
            headerName1: "EquipName"
            headerName2: "EquipID"
            roleName1:"name"
            roleName2:"id"
            function sendToNextPage(viewId, data) {
                viewId.push("qrc:/ModifyDBPageEquipObject.qml", { equipmentTypeName: equipmentTypeName, equipmentTypeId: equipmentTypeId,
                                                                equipmentName:data["name"], equipmentId:data["id"] })
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
                id: newEquipItem
                anchors.topMargin: 50
                anchors.top: parent.top
                height: 20

                Behavior on anchors.topMargin { SmoothedAnimation { velocity: 50 }}
                Behavior on height { SmoothedAnimation { velocity: 500 }}
                CheckBox {
                    id: newEquipUseTemplateCheckbox
                    checked: false
                    height: 20
                    text: qsTr("以现有开关柜作为模板")
                    onCheckedChanged: {
                       if(checked){
                            chooseCopyEquipTemplateModule.visible = true
                            newEquipItem.height = 250
                            newEquipItem.anchors.topMargin = 10
                       }
                       else{
                            chooseCopyEquipTemplateModule.visible = false
                            newEquipItem.height = 20
                           newEquipItem.anchors.topMargin = 50

                       }
                    }
                }
                Item{
                    id: chooseCopyEquipTemplateModule
                    visible: false

                    anchors.top: newEquipUseTemplateCheckbox.bottom
                    Label{
                        id: newEquipSelectorInfoLabel
                        text: "请选择模板"
                        color: "slategray"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.leftMargin: 100
                        anchors.left: parent.left
                        width: 50
                        height: 20
                        anchors.bottomMargin: 10

                    }
                    Label{
                        id: newEquipTypeLabel
                        text: "EquipType"
                        verticalAlignment: Text.AlignVCenter
                        anchors.top: newEquipSelectorInfoLabel.bottom
                        anchors.topMargin: 10
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                        width: 50
                        height: 35
                        anchors.bottomMargin: 20


                    }
                    ComboBox {
                        id:newEquipTypeTemplateSelector
                        anchors.top:newEquipTypeLabel.top
                        anchors.left: newEquipTypeLabel.right
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 40
                        height: 35
                        editable: false
                        textRole: "name"
                        model: equipTypeModel
                        Component.onCompleted:{
                            currentIndex = find(equipmentTypeName)
                            var currentItem = delegateModel.items.get(currentIndex)
                            equipTypeForCopySignal(currentItem.model.id)

                        }
                        onCurrentTextChanged: {
                            console.log("currentText", currentText)
                            if(currentText !== equipmentTypeName){

                                errorOutputLabel.text = "警告:当前正在进行跨类别复制"
                                errorOutputLabel.color = "orange"
                            }
                            else{
                                errorOutputLabel.text = ""
                            }
                            var currentItem = delegateModel.items.get(currentIndex)
                            equipTypeForCopySignal(currentItem.model.id)
                        }
                    }
                    Label{
                        id: newEquipLabel
                        text: "EquipName"
                        verticalAlignment: Text.AlignVCenter
                        anchors.top: newEquipTypeLabel.bottom
                        anchors.topMargin: 10
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                        width: 50
                        height: 35

                    }
                    ComboBox {
                        id:newEquipTemplateSelector
                        anchors.top:newEquipLabel.top
                        anchors.left: newEquipLabel.right
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 40
                        height: 35
                        editable: false
                        textRole: "name"
                        model: equipNameForCopyModel
                        Component.onCompleted: currentIndex=0
                    }
                    Label{
                        id: newEquipQRInfoLabel
                        text: "请输入新配电柜QRCode信息"
                        color: "slategray"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.top: newEquipLabel.bottom
                        anchors.topMargin: 10
                        anchors.leftMargin: 80
                        anchors.left: newEquipLabel.left
                        width: 50
                        height: 20
                        anchors.bottomMargin: 10

                    }
                    TextField {
                        id:newEquipQRCode0
                        anchors.top:newEquipQRInfoLabel.bottom
                        anchors.left: newEquipLabel.left
                        anchors.topMargin: 10
                        anchors.right: newEquipTemplateSelector.right
                        height: 35
                        placeholderText: qsTr("请输入QRCode0的内容")
                    }
                    TextField {
                        id:newEquipQRCode1
                        anchors.top:newEquipQRCode0.bottom
                        anchors.left: newEquipQRCode0.left
                        anchors.right: newEquipTemplateSelector.right
                        anchors.topMargin: 10
                        height: 35
                        placeholderText: qsTr("请输入QRCode1的内容")
                    }
                }
                Item {

                }
            }
            TextField {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 20
                anchors.top: newEquipItem.bottom
                id: newEquipNameInput
                placeholderText: qsTr("新建配电柜的EquipName")
            }
            Button{
                id: newEquipNameButton
                anchors.top: newEquipNameInput.bottom
                anchors.topMargin: 20
                anchors.right: newEquipNameInput.right
                text: qsTr("新建")
                onClicked: {
                    if(newEquipNameInput.text === ""){
                        console.log("The input 'newEquipName' is empty!")
                        errorOutputLabel.text = "错误: EquipName为空！"
                        errorOutputLabel.color = "red"
                        return
                    }
                    errorOutputLabel.text = ""
                    errorOutputLabel.color = "red"

                    equipNameModelManager.addToDB(newEquipNameInput.text, equipmentTypeId)
                    if(newEquipUseTemplateCheckbox.checked){
                        equipNameModelManager.copyVisualObjectsOfEquipment(equipmentTypeId, newEquipTemplateSelector.currentText, newEquipNameInput.text, newEquipQRCode0.text, newEquipQRCode1.text);
                    }
                }
            }
            Label{
                id:errorOutputLabel
                color: "red"
                height: 20
                anchors.top: newEquipNameButton.bottom
                wrapMode:Text.Wrap

            }
        }
    }
    footer: Label{
        id: currentSelectedEquipType
        font.pixelSize: 15
        text: qsTr("已选择配电柜 类型:") + equipmentTypeName
    }
}










































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
