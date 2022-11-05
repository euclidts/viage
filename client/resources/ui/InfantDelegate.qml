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

    Label {
        Layout.margins: 6
        text: title + ' ' + (model.index + 1)
        font.bold: true
    }

    SexChooser {
        sexOf: model
    }

    PersonDelegate {
        model: root.model
    }
}
