import QtQuick
import QtQuick.Dialogs
import QtCore

Item {
    property alias folderDialog: folderDialog
    property alias fileDialog: fileDialog
    property string path
    property var jsonMetadata
    property var func

    FolderDialog {
        id: folderDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        onAccepted: {
            path = currentFolder
            func()
        }
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        nameFilters: ["(*.pdf *.png *.jpg *.jpeg *.raw *.tiff)", "(*)"]
        onAccepted: {
            path = currentFile
            func()
        }
    }
}
