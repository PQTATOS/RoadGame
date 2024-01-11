import QtQuick 2.0
import Sailfish.Silica 1.0
import src 1.0

Page {
    objectName: "levelSelectPage"
    allowedOrientations: Orientation.All
    Button{
        onClicked: {
            pageStack.replace(Qt.resolvedUrl("MainPage.qml"))
        }
    }
}
