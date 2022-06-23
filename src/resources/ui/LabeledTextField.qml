import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ColumnLayout {
    spacing: 0

    property string placeHolder: qsTr("* Champ Obligatoire")
    property alias validator: field.validator
    property alias text: field.text
    required property string name
    required property string textOf
    required property var onEdit
    property int inputHint: Qt.ImhNone
    property int capitalization: Font.Capitalize

    Label {
        id: label
        text: name
        font.italic: true
    }

    TextField {
        id: field
        text: textOf
        onEditingFinished: onEdit(text)
        inputMethodHints: inputHint
        placeholderText: placeHolder
        Layout.fillWidth: true
        font.capitalization: capitalization
        onAccepted: focus = false
        onTextChanged: acceptableInput ? color = Material.foreground
                                       : color = "red"
    }
}
