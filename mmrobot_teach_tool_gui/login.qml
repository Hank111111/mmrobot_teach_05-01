import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
Item {
    id: name
    
    Component.onCompleted:   username_input.focus = true
    Text {
        id: user_name_display
        x: 144
        y: 178
        text: qsTr("账号")
        font.pixelSize: 12
    }
    TextField {
        id: username_input
        x: 220
        y: 167
        width: 279
        height: 40
        placeholderText: qsTr("")
        focus: true
        
    }
    Text {
        id: password_display
        x: 144
        y: 248
        text: qsTr("密码")
        font.pixelSize: 12
    }
    TextField {
        id: password_input
        x: 221
        y: 237
        width: 278
        height: 40
        placeholderText: qsTr("")
        echoMode: TextInput.Password
        Keys.onReturnPressed: {
            establishConnect()
        }
    }

    Button {
        id: login
        x: 428
        y: 312
        width: 71
        height: 29
        text: "登录"
        onClicked:{
            establishConnect()
        }
        Keys.onReturnPressed: {
            establishConnect()
        }
    }

    Text {
        id: element
        x: 141
        y: 91
        width: 358
        height: 44
        text: qsTr("请输入具有管理员权限的数据库账号与密码")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 17
    }

    Label {
        id: error_info
        anchors.top : login.bottom
        anchors.left : element.left
        color: "red"
        
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 17

        width: 300
        height: 50
        wrapMode:Text.Wrap
    }
    function establishConnect() {
        var ret = DBInterface.establishSQLConn("127.0.0.1", username_input.text, password_input.text, "Power_distribution_room")
        if(ret){
            stackView.push("qrc:/MenuSelectPage.qml")
            equipTypeModelManager.retrieveFromDB()
        }
        else{
            error_info.text = DBInterface.getErrorMsg()
        }
    }
    
}



























/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
