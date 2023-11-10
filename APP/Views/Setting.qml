import QtQuick 2.3
import QtQuick.Window 2.3

Window {
    id: setting
    visible: false
    width: 800
    height: 600
    minimumWidth: 500
    minimumHeight: 300
    title: qsTr("设置")
    color: theme.background

    Text {
        anchors.centerIn: parent
        text: "Hello, World!"
    }
}
