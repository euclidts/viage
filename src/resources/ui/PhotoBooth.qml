import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

Rectangle {
    anchors.centerIn: parent
    anchors.fill: parent
    visible: false
    color: "transparent"

    property string path
    property var jsonMetadata
    property var func
    property alias loader: cameraLoader

    Loader {
        id: cameraLoader
        anchors.fill: parent
        source: "qrc:/ui/CameraScene.qml"
        active: false

        onActiveChanged:
            if (active) {
                parent.visible = true
                item.onValidate = func
                item.path = path
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
