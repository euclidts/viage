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
    property int minIndex: 0

    RowLayout {
        Label {
            Layout.margins: 6
            text: title + ' ' + (model.index + 1)
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        RoundButton {
            id: deleteButton
            icon.source: "qrc:/icons/trash-alt.svg"
            visible: model.index >= minIndex
            onClicked: {
                owners.remove(model.id)
            }
        }
    }

    SexChooser {
        sexOf: model
    }

    PersonDelegate {
        Layout.fillWidth: true
        model: root.model
    }
}
