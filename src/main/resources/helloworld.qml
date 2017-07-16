import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    title: "Qt Quick2 Hello World"
    width: 480
    height: 320
    visible: true
    background: Rectangle {
        anchors.fill: parent
        color: "black"
    }

        Text {
            id: hello
            text: "Hello "
            font.family: 'serif'
            font.pointSize: 48
            visible:false
        }
        LinearGradient {
            anchors.fill: hello
            source: hello
            start:Qt.point(0,0)
            end: Qt.point(0, hello.height)
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "palegreen"
                }
                GradientStop {
                    position: 1
                    color: "seagreen"
                }
            }
        }
        Text {
            id: world
            anchors.left: hello.right
            anchors.leftMargin: 4
            text: "World!!!"
            font.family: 'serif'
            font.pointSize: 48
            visible: false
        }
        DropShadow {
            anchors.fill: world
            source: world
            color: "dodgerblue"
            radius: 25
            samples: 51
            spread: 0.25
        }
        LinearGradient {
            anchors.fill: world
            source: world
            start:Qt.point(0,0)
            end: Qt.point(0, world.height)
            gradient: Gradient {
                GradientStop{position:0;color:"cyan"}
                GradientStop{position:1;color:"dodgerblue"}
            }
        }
}
