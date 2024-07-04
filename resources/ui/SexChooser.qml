import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ColumnLayout {

    required property var sexOf

    ButtonGroup {
        id: sexGroup
        buttons: sexRow.children
        onCheckedButtonChanged: sexOf.sex = checkedButton.index
    }

    RowLayout {
        id: sexRow
        spacing: 0
        Layout.margins: 0

        RadioButton {
            text: qsTr("Monsieur")
            readonly property int index: 0
            checked: sexOf.sex === index
        }

        RadioButton {
            text: qsTr("Madame")
            readonly property int index: 1
            checked: sexOf.sex === index
        }
    }
}
