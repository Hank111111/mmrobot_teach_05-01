import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Page {
    property string equipmentName: "unknown"
    property string equipmentTypeName: "unknown"

    property string visualObjName: "unknown"
    property int objectUniqueId: -1
    property int equipmentId: -1
    property int equipmentTypeId: -1

    onObjectUniqueIdChanged: objAttribs.objUniqueId=objectUniqueId
    onEquipmentIdChanged: objAttribs.equipId=equipmentId
    onEquipmentTypeIdChanged: objAttribs.equipTypeId = equipmentTypeId



    header: ToolBar {

        ToolButton {
            text: qsTr("上一步")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }
        Label {
            text: qsTr("修改元件属性")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
    GridLayout {
        id: grid
        columns: 4
        rows: 7
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.leftMargin: 30

        LabelInputBox {
            id: attribX
            labelName: "x"
            setValue:objAttribs.posX.toFixed(5);
            Layout.column: 0
            Layout.row: 0
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText

            onTextChanged:{
                if(setValue !== objAttribs.posX) objAttribs.posX = setValue;
                console.log("setValue %s", objAttribs.posX)
            }
            validator: DoubleValidator {}
            focus: true

        }
        LabelInputBox {
            id: attribY
            labelName: "y"
            setValue:objAttribs.posY.toFixed(5);
            Layout.column: 1
            Layout.row: 0
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            onTextChanged:{
                if(setValue !== objAttribs.posY) objAttribs.posY = setValue;
                console.log("setValue %s", objAttribs.posY)
            }
            validator: DoubleValidator {}
        }
        LabelInputBox {
            id: attribZ
            labelName: "z"
            setValue:objAttribs.posZ.toFixed(5);
            Layout.column: 2
            Layout.row: 0
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.posZ) objAttribs.posZ = setValue;
                console.log("setValue %s", objAttribs.posZ)
            }
        }

        LabelInputBox {
            id: attribAdditionalInfo
            labelName: "QRCode Info"
            setInputMethodHintsValue : Qt.ImhNone| Qt.ImhNoPredictiveText
            setValue:objAttribs.additionalInfo
            Layout.column: 3
            Layout.row: 0
            visible: (visualObjName == "QRCode")? true: false
            onTextChanged:{
                if(setValue !== objAttribs.additionalInfo) objAttribs.additionalInfo = setValue;
                console.log("setValue %s", objAttribs.additionalInfo)
            }
        }
        LabelInputBox {
            id: attribQX
            setValue:objAttribs.quatX.toFixed(5);
            labelName: "qx"
            Layout.column: 0
            Layout.row: 1
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            isValid: objAttribs.quatValid
            onTextChanged:{
                console.log("quatValid: ",objAttribs.quatValid)
                if(setValue !== objAttribs.quatX) objAttribs.quatX = setValue;
                console.log("setValue %s", objAttribs.quatX)
                objAttribs.checkQuatValid()

            }
        }
        LabelInputBox {
            id: attribQY
            setValue:objAttribs.quatY.toFixed(5);
            labelName: "qy"
            Layout.column: 1
            Layout.row: 1
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            isValid: objAttribs.quatValid
            onTextChanged:{
                if(setValue !== objAttribs.quatY) objAttribs.quatY = setValue;
                console.log("setValue %s", objAttribs.quatY)
                objAttribs.checkQuatValid()

            }
        }
        LabelInputBox {
            id: attribQZ
            setValue:objAttribs.quatZ.toFixed(5);
            labelName: "qz"
            Layout.column: 2
            Layout.row: 1
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            isValid: objAttribs.quatValid
            onTextChanged:{
                if(setValue !== objAttribs.quatZ) objAttribs.quatZ = setValue;
                console.log("setValue %s", objAttribs.quatZ)
                objAttribs.checkQuatValid()
            }
        }

        LabelInputBox {
            id: attribQW
            setValue: objAttribs.quatW.toFixed(5);
            validator: DoubleValidator {}
            isValid: objAttribs.quatValid
            labelName: "qw"
            Layout.column: 3
            Layout.row: 1
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText

            onTextChanged:{

                if(setValue !== objAttribs.quatW) objAttribs.quatW = setValue;
                console.log("setValue %s", objAttribs.quatW)
                objAttribs.checkQuatValid()
            }
        }

        LabelInputBox {
            id: attribWidth
            setValue: objAttribs.sizeWidth.toFixed(5);
            labelName: "width"
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.sizeWidth) objAttribs.sizeWidth = setValue;
                console.log("setValue %s", objAttribs.sizeWidth)
            }
            Layout.column: 0
            Layout.row: 2
        }

        LabelInputBox {
            id: attribHeight
            setValue:objAttribs.sizeHeight.toFixed(5);
            labelName: "height"
            Layout.column: 1
            Layout.row: 2
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.sizeHeight) objAttribs.sizeHeight = setValue;
                console.log("setValue %s", objAttribs.sizeHeight)
            }
        }

        LabelInputBox {
            id:  attribCanAutoRefine
            setValue:objAttribs.canAutoRefine;
            labelName: "auto refine"
            Layout.column: 2
            Layout.row: 2
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: IntValidator {
                bottom: 0
                top: 1
            }
            onTextChanged:{
                if(setValue !== objAttribs.canAutoRefine) objAttribs.canAutoRefine = setValue;
                console.log("setValue %s", objAttribs.canAutoRefine)
            }
        }

        LabelInputBox {
            id: attribBestCapOffsetX
            setValue:objAttribs.bestCapOffsetX.toFixed(5);
            labelName: "best cap offset x"
            Layout.column: 0
            Layout.row: 3
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.bestCapOffsetX) objAttribs.bestCapOffsetX = setValue;
                console.log("setValue %s", objAttribs.bestCapOffsetX)
            }
        }

        LabelInputBox {
            id: attribBestCapOffsetY
            setValue:objAttribs.bestCapOffsetY.toFixed(5);
            labelName: "best cap offset y"
            Layout.column: 1
            Layout.row: 3
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.bestCapOffsetY) objAttribs.bestCapOffsetY = setValue;
                console.log("setValue %s", objAttribs.bestCapOffsetY)
            }
        }
        LabelInputBox {
            id: attribBestCapOffsetZ
            setValue:objAttribs.bestCapOffsetZ.toFixed(5);
            labelName: "best cap offset z"
            Layout.column: 2
            Layout.row: 3
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.bestCapOffsetZ) objAttribs.bestCapOffsetZ = setValue;
                console.log("setValue %s", objAttribs.bestCapOffsetZ)
            }
        }

        Label {
            Layout.column: 0
            Layout.row:4
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 200
            Layout.minimumHeight: 50
            anchors.topMargin: 30
            text: "仅针对手车开关:"
            color: "steelblue"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        LabelInputBox {
            id: attribRadius
            setValue:objAttribs.radius.toFixed(5);
            labelName: "radius"
            labelColor: "steelblue"
            Layout.column: 1
            Layout.row: 4
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.radius) objAttribs.radius = setValue;
                console.log("setValue %s", objAttribs.radius)
            }
        }
        LabelInputBox {
            id: attribTrunkSquareSize
            setValue:objAttribs.trunkSquareSize.toFixed(5);
            labelName: "trunk square size"
            labelColor: "steelblue"
            Layout.column: 2
            Layout.row: 4
            setInputMethodHintsValue: Qt.ImhFormattedNumbersOnly| Qt.ImhNoPredictiveText
            validator: DoubleValidator {}
            onTextChanged:{
                if(setValue !== objAttribs.trunkSquareSize) objAttribs.trunkSquareSize = setValue;
                console.log("setValue %s", objAttribs.trunkSquareSize)
            }
        }
        Item {
            Layout.column: 0
            Layout.row:5
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 200
            Layout.minimumHeight: 50

        }

        Button{
            Layout.column: 3
            Layout.row: 6

            id:modifyObjAttribConfirmButton
            text: qsTr("保存")
            onClicked: {
                objAttribs.saveMembers()
            }

        }
        Button{
            Layout.column: 2
            Layout.row:  6

            id:modifyObjAttribResetButton
            text: qsTr("重置")
            onClicked:
            {
                objAttribs.readMembers()

            }
        }
        Button{
            Layout.column: 1
            Layout.row: 6

            id:normalizeQuat
            text: qsTr("归一化四元数")
            onClicked:
            {
                objAttribs.normalizeQuat()

            }
        }
    }
    footer: Label{
        id: currentSelectedEquipType
        font.pixelSize: 15
        text: qsTr("已选择配电柜 类型:") + equipmentTypeName + qsTr(", 名称: ") + equipmentName + qsTr(", 元件: ") + visualObjName + qsTr(" UniqueId=") + String(objectUniqueId)
    }

}




