import QtQuick
import QtQuick.Dialogs
import QtCore

Rectangle {
    anchors.centerIn: parent
    anchors.fill: parent
    visible: false
    color: "transparent"

    property alias loader: cameraLoader
    property string path
    property var jsonMetadata
    property var func

    Loader {
        id: cameraLoader
        anchors.fill: parent
        source: "qrc:/ui/CameraScene.qml"
        active: false

        onActiveChanged:
            if (active) {
                parent.visible = true
                item.onValidate = func
                topBar.visible = false
                rootStack.visible = false
                bottomBar.visible = false
            } else {
                parent.visible = false
                topBar.visible = true
                rootStack.visible = true
                bottomBar.visible = true
            }
    }
}
