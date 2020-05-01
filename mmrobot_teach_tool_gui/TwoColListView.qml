import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.13

Rectangle{
    color: 'lightcyan'
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.minimumWidth: 100
    Layout.preferredWidth: 150
    Layout.maximumWidth: 300
    Layout.minimumHeight: 150
    id: twoColListViewRoot
    property var implementedModel: equipTypeModel
    property string headerName1: "TypeName"
    property string headerName2: "TypeID"
    property string roleName1:"name"
    property string roleName2:"id"

    RowLayout{
        id: headerRow
        anchors.top: parent.top
        anchors.left: parent.left
        width: 200
        height:50
        anchors.leftMargin: 50
        anchors.rightMargin: 25
        Label {
            width: parent.width * 0.6
            Layout.fillHeight: true
            height: parent.height
            text: twoColListViewRoot.headerName1
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }


        Item{
            height: parent.height
            width: parent.width * 0.2
            //Rectangle { anchors.fill: parent; color: "#ffaaaa" }
        }

        Label {
            width: parent.width * 0.2
            Layout.fillHeight: true
            text: twoColListViewRoot.headerName2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
    ListView {
        id: listViewOfType
        //anchors.verticalCenter: parent.RowLayout.verticalCenter
        anchors.left: twoColListViewRoot.left
        anchors.top: headerRow.bottom
        anchors.leftMargin: 50
        anchors.rightMargin: headerRow.rightMargin

        topMargin: 25
        width: headerRow.width
        height: parent.height - headerRow.height - 50
        clip: true
        model: twoColListViewRoot.implementedModel
        delegate: ItemDelegate {
            id: delegateItem
            width: parent.width
            height: 50
            Row{
                width: parent.width
                height: parent.height
                Label{
                    width: parent.width * 0.6
                    height: parent.height
                    text: model[twoColListViewRoot.roleName1]
                    verticalAlignment: Text.AlignVCenter
                }
                Item{
                    height: parent.height
                    width: parent.width * 0.2
                    //Rectangle { anchors.fill: parent; color: "#ffaaaa" }
                }

                Label{
                    width: parent.width * 0.2
                    height: parent.height
                    text: model[twoColListViewRoot.roleName2]
                    verticalAlignment: Text.AlignVCenter
                }
            }

            onClicked: {
                sendToNextPage(stackView, model)
            }

        }

    }
}














































































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
