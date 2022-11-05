import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

RowLayout {
    spacing: 0

    property var onFieldAccepted
    property alias fieldFocus: field.focus
    property string placeholder: qsTr("Mot de passe")
    property alias text: field.text

    TextField {
        id: field
        Layout.fillWidth: true
        placeholderText: placeholder
        echoMode: echoSwitch.checked ? TextInput.Normal
                                     : TextInput.Password
        onAccepted: onFieldAccepted()
    }

    Button {
        id: echoSwitch
        flat: true
        checkable: true
        icon.source: checked ? "qrc:/icons/eye-slash.svg"
                             : "qrc:/icons/eye.svg"
        Layout.alignment: Qt.AlignLeft
        background: Rectangle {
            radius: 2
            color: Material.buttonDisabledColor

            PaddedRectangle {
                y: field.height - height - field.bottomPadding + 3
                width: parent.width
                height: field.activeFocus || field.hovered ? 2 : 1
                color: field.activeFocus ? Material.accentColor
                                           : (field.hovered ? Material.primaryTextColor : Material.hintTextColor)
                topPadding: -2
                clip: true
            }

            Ripple {
                clipRadius: 2
                width: parent.width
                height: parent.height
                pressed: echoSwitch.pressed
                anchor: echoSwitch
                color: echoSwitch.flat && echoSwitch.highlighted ? Material.highlightedRippleColor : Material.rippleColor
            }
        }
    }
}
