import QtQuick
import QtQuick.Dialogs
import QtCore

Rectangle {
    anchors.centerIn: parent
    anchors.fill: parent
    visible: false
    color: "transparent"

    property alias folderDialog: folderDialog
    property alias fileDialog: fileDialog
    property alias camerLoader: cameraLoader
    property string path
    property var jsonMetadata
    property var func

    FolderDialog {
        id: folderDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        onAccepted: {
            urlProvider.path = currentFolder
            urlProvider.func()
        }
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        nameFilters: ["(*.pdf *.png *.jpg *.jpeg *.raw *.tiff)", "(*)"]
        onAccepted: {
            urlProvider.path = currentFile
            urlProvider.func()
        }
    }

    Loader {
        id: cameraLoader
        anchors.fill: parent
        source: "qrc:/ui/CameraScene.qml"
        active: false

        onActiveChanged:
            if (active) {
                urlProvider.visible = true
                item.onValidate = urlProvider.func
                item.path = urlProvider.path
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
