import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

GroupBox {
    id: root
    label: Label {
        text: qsTr("Address")
        font.italic: true
    }
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var addressOf
    required property bool canEdit

    ColumnLayout {
        width: parent.width

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 12
            visible: canEdit

            LabeledTextField {
                name: qsTr("Rue")
                textOf: addressOf.street
                canEdit: root.canEdit
                onEdit: function(txt) { addressOf.street = txt }
            }

            LabeledTextField {
                name: qsTr("Ville")
                textOf: addressOf.city
                canEdit: root.canEdit
                onEdit: function(txt) { addressOf.city = txt }
            }

            GridLayout {
                columns: 2
                Layout.fillWidth: true

                Label {
                    text: qsTr("Code Postal")
                    font.italic: true
                    Layout.alignment: Qt.AlignHCenter
                }

                Label {
                    text: qsTr("Canton")
                    font.italic: true
                }

                SpinBox {
                    from: 1000
                    to: 4000
                    editable: true
                    value: addressOf.zip
                    onValueModified: addressOf.zip = value
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    Layout.maximumWidth: 130
                    textFromValue: function(value, locale) {
                        return Number(value).toString();
                    }
                    // Workaround
                    up.onPressedChanged: {
                        streetField.focus = false
                        cityField.focus = false
                    }
                    down.onPressedChanged: {
                        streetField.focus = false
                        cityField.focus = false
                    }
                }

                ComboBox {
                    id: cantonField
                    model: SwissCantons {}
                    Layout.minimumWidth: 164
                    onActivated: addressOf.canton = currentValue
                    Component.onCompleted: currentIndex = indexOfValue(addressOf.canton)
                }
            }
        }

        TextField {
            text: addressOf.street + ' ' + addressOf.city + ' ' + addressOf.zip + ' ' + addressOf.canton
            readOnly: true
            visible: !canEdit
            Layout.fillWidth: true
        }
    }
}
