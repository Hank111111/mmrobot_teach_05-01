import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5
Page {
    id: menu_select_page
    header: ToolBar {
        Label {
            text: qsTr("Home")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
    Button {
        id: button
        x: 220
        y: 100
        width: 200
        height: 60
        text: qsTr("修改数据库")
        onClicked: stackView.push("qrc:/ModifyDBPageEquipType.qml")
    }

    Button {
        id: button1
        x: 220
        y: 200
        width: 200
        height: 60
        text: qsTr("示教")
        onClicked: stackView.push("qrc:/TeachCabinetPosPage.qml")

    }

    Button {
        id: button2
        x: 220
        y: 300
        width: 200
        height: 60
        text: qsTr("使VisualWrapper重载
        数据库")
        onClicked: reReadDatabaseMsgPublisher.publish()

    }

}




































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
