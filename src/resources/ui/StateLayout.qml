import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

RowLayout {
    property bool flagged
    required property int nameIndex
    required property var date

    MaterialButton {
        fillWidth: false
        text: stateNames[nameIndex]
        icon.source: flagged ? "qrc:/icons/square-check.svg"
                             : "qrc:/icons/square.svg"
        icon.color: flagged ? Material.highlightedButtonColor
                            : Material.primaryTextColor
        onClicked: if (bridge.clearance === 4) {
                       let tag = Math.pow(2, nameIndex - 2)

                       flagged ? bridge.updateState(-tag)
                               : bridge.updateState(tag)
                   }
    }

    Label {
        text: flagged ? Qt.formatDate(date, "dd.MM.yy")
                                     : ""
    }
}
