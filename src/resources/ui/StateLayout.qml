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
                       let tag = Math.pow(2, nameIndex - 1)

                       if (flagged) {
                           if (!bridge.accountHasFlag(Math.pow(2, nameIndex)))
                               bridge.updateState(-tag)
                           else
                               return
                       } else {
                           if (bridge.accountHasFlag(Math.pow(2, nameIndex - 2)))
                               bridge.updateState(tag)
                           else
                               return
                       }

                       busyDialog.open()
                   }
    }

    Label {
        text: Qt.formatDate(validation, "dd.MM.yy")
        visible: flagged
    }
}
