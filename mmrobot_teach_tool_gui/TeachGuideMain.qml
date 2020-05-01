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
            text: qsTr("选择示教方式")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }




    Button {
        id: buttonTeachGuided
        x: 220
        y: 91
        width: 200
        height: 75
        text: qsTr("引导式示教")
        onClicked: stackView.push("qrc:/TeachCabinetPosPage.qml")
    }

    Button {
        id: buttonTeachAdvance
        x: 220
        y: 262
        width: 200
        height: 73
        text: qsTr("高级功能")
        onClicked: stackView.push("qrc:/TeachGuideMain.qml")

    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
