import QtQuick 2.0
import QtQuick.Controls 2.5
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    color: "#ffffff"
    title: qsTr("机器人示教")
    id: root
    ModifyDBStackView {
        id: stackView
    }
    signal equipTypeSignal(int typeMsg)
    signal equipTypeForCopySignal(int typeMsg)
    signal equipIdSignal(int typeMsg, int idMsg)
}
