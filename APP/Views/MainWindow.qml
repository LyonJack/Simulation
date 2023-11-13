import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import MainViewModel 1.0
import QtGraphicalEffects 1.15
import MapItem 1.0
import QuickPaintedItem 1.0


Window {
    visible: true
    width: 800
    height: 600
    minimumWidth: 500
    minimumHeight: 300
    title: theme.title
    color: theme.background

    MainViewModel{
        id: dataContext
    }

    Theme
    {
        id: theme
    }

    SettingWindow
    {
        id: setting
    }

    Rectangle{
        anchors.fill: parent
        color: theme.background

        Column {
            anchors.centerIn: parent
            spacing: 5

            TextArea {
                id: nameTextArea
                color: theme.foreground
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("username")
                text: dataContext.name
                onTextChanged: dataContext.name = text
                KeyNavigation.tab: passwordTextArea
            }

            TextArea {
                id: passwordTextArea
                color: theme.foreground
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("password")
                text: dataContext.password
                onTextChanged: dataContext.password = text
            }

            Button {
                text: "Login"
                height: 20
                width: 20
                anchors.right: parent.right
                anchors.rightMargin: 5
                background : Rectangle
                {
                    color:  theme.background
                }

                onClicked: {setting.show()}
                //onClicked: dataContext.loginButtonClicked()

                Image {
                    id: image
                    fillMode: Image.PreserveAspectFit
                    height: 30
                    width: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "../Images/setting.svg"
                    ColorOverlay{
                        anchors.fill: image
                        source: image
                        color: "#FF6100"
                    }
                }
            }

            Text {
                id:stateText
                anchors.horizontalCenter: parent.horizontalCenter
                text: dataContext.state
            }
        }
    }


    Rectangle {
        visible: true
        width: 640
        height: 480
        color: "#2795e9"
        border.color: red
        MapItem
        {
            id: mapItem
            anchors.fill: parent
            MouseArea
            {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onWheel:{
                    parent.onWheel(wheel.x,wheel.y,wheel.angleDelta.y)
                }
            }
        }
    }

    QuickPaintedItem {
            id: drawer
            anchors.fill: parent
            antialias: true
            MouseArea{
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                hoverEnabled:true

                onPressed: {
                    if(mouse.button == Qt.LeftButton){
                        drawer.draw = true;
                        parent.mousePress(mouseX,mouseY)
                    }
                    else{
                        drawer.draw = false;
                    }
                }
                onPositionChanged: {
                    parent.mouseMove(mouseX,mouseY)
                }
                onReleased: {
                    if(mouse.button == Qt.LeftButton)
                        parent.mouseRelease(mouseX,mouseY)
                }
            }
        }
}
