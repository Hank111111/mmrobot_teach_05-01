import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13
import QtQuick.Controls.Styles 1.4

ColumnLayout{
    
    property alias labelName: label.text
    property alias labelColor: label.color
    property alias setValue: textField.text
    property alias setInputMethodHintsValue: textField.inputMethodHints
    property alias validator: textField.validator
    property bool isValid: true
    signal textChanged
    spacing: 5
    id: label_input_box
    Layout.minimumWidth: 50
    Layout.preferredWidth: 100
    Layout.maximumWidth: 200
    Layout.minimumHeight: 50

    onIsValidChanged:{
        console.log("isvalid changed ", isValid)
        setTextGroundColor()
    }
    function setTextGroundColor(){
        textField.background.border.color = (textField.acceptableInput && isValid) ? "black" : "red"
    }

    Label{
        id: label
        Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
        verticalAlignment: Text.AlignBottom
        Layout.fillWidth: true
        Layout.minimumWidth: 30
        Layout.preferredWidth: 30
        Layout.maximumWidth: 50
        Layout.minimumHeight: 30

    }
    TextField{
        id: textField
        Layout.alignment: Qt.AlignLeft
        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 100
        Layout.minimumHeight: 20
        selectByMouse: true
        onEditingFinished: {
            label_input_box.textChanged()
            console.log("setValue ", text," ,", setValue)
            background.border.color = (acceptableInput && isValid) ? "black" : "red"

        }

        background: Rectangle {
            radius: 2
            implicitWidth: parent.width
            implicitHeight: parent.height
            border.color: 'black'
            border.width: 1
        }
        activeFocusOnPress:true
        selectionColor:"gray"
        selectedTextColor:"white"
        onFocusChanged: {
            focus ? selectAll() : deselect()
            if (acceptableInput && isValid){
                background.border.color = focus ? "blue":"black"

            }
            else {
                background.border.color = "red"
            }

        }
        horizontalAlignment:TextInput.AlignLeft

    }
}
