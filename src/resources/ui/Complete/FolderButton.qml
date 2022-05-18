import QtQuick.Controls
import QtQuick.Controls.Material

import Complete

RoundButton {
    icon.source: "qrc:/icons/folder-open.svg"
    icon.width: height * 0.4
    onClicked: {
        urlProvider.jsonMetadata = jsonMetadata
        urlProvider.func = updateFunc
        urlProvider.fileDialog.open()
    }
}
