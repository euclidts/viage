import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

ColumnLayout {
    spacing: 0
    Layout.fillWidth: true

    required property int numberOf
    required property string name
    property var onEdit
    property int minimum: 0
    property int maximum

    Label {
        text: name
        font.italic: true
        Layout.alignment: Qt.AlignHCenter
    }

    SpinBox {
        from: minimum
        to: maximum
        editable: true
        value: numberOf
        onValueModified: onEdit(value)
        inputMethodHints: Qt.ImhFormattedNumbersOnly
        Layout.maximumWidth: 130
        textFromValue: function(value, locale) {
            return Number(value).toString();
        }
    }
}
