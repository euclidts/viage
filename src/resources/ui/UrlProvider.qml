import QtQuick

Rectangle {
    anchors.centerIn: parent
    anchors.fill: parent
    visible: false
    color: "transparent"

    property alias camerLoader: cameraLoader
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
                urlProvider.visible = true
                item.onValidate = func
                item.path = path
                topBar.visible = false
                rootStack.visible = false
                bottomBar.visible = false
            } else {
                urlProvider.visible = false
                topBar.visible = true
                rootStack.visible = true
                bottomBar.visible = true
            }
    }
}
