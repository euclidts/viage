import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ColumnLayout {
    id: root
    spacing: 0
    width: parent.width
    Layout.minimumWidth: 200
    Layout.margins: 6

    required property var model
    required property string title
    property bool editing: true

    Label {
        Layout.margins: 6
        text: title + ' ' + (model.index + 1)
        font.bold: true
    }

    ButtonGroup {
        id: sexGroup
        buttons: sexRow.children
        onCheckedButtonChanged: model.sex = checkedButton.index
    }

    RowLayout {
        id: sexRow
        spacing: 0
        Layout.margins: 0
        visible: root.editing

        RadioButton {
            text: qsTr("Monsieur")
            readonly property int index: 0
            checked: model.sex === index
        }

        RadioButton {
            text: qsTr("Madame")
            readonly property int index: 1
            checked: model.sex === index
        }
    }

    TextField {
        id: sexDisplay
        Layout.leftMargin: 12
        Layout.rightMargin: 12
        text: sexGroup.checkedButton.text
        readOnly: true
        Layout.fillWidth: true
        visible: !root.editing
    }

    PersonDelegate {
        Layout.fillWidth: true
        editing: root.editing
        model: root.model
    }
}
