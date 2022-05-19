import QtQuick.Controls
import QtQuick.Controls.Material

RoundButton {
    icon.source: "qrc:/icons/download.svg"
    visible: model.isUploaded
    onClicked: {
        urlProvider.func = function() {
            bridge.downloadFile("documents/" + model.id + "/body",
                                urlProvider.path,
                                flieName.text)
        }
        urlProvider.folderDialog.open()
    }
}
