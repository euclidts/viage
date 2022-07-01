import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Interface

RowLayout {
    property bool flagged
    required property int nameIndex
    property date validation

    MaterialButton {
        fillWidth: false
        text: stateNames[nameIndex]
        icon.source: flagged ? "qrc:/icons/check-square.svg"
                             : "qrc:/icons/square.svg"
        onClicked: if (bridge.clearance === 4) {
                       busyDialog.open()
                       let tag = Math.pow(2, nameIndex - 1)

                       flagged ? bridge.updateState(-tag)
                               : bridge.updateState(tag)
                   }
    }

    Label {
        text: Qt.formatDate(validation, "dd.MM.yy")
        visible: flagged
    }
}
