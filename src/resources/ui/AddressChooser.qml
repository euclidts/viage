import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

GroupBox {
    id: root
    label: Label {
        text: qsTr("Adresse")
        font.italic: true
    }
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var addressOf

    ColumnLayout {
        width: parent.width

        GridLayout {
            columns: portrait ? 1 : 2
            Layout.fillWidth: true

            LabeledTextField {
                name: qsTr("Rue")
                textOf: addressOf.street
                onEdit: function(txt) { addressOf.street = txt }
                capitalization: Font.MixedCase
            }

            LabeledTextField {
                name: qsTr("Ville")
                textOf: addressOf.city
                onEdit: function(txt) { addressOf.city = txt }
                capitalization: Font.MixedCase
            }
        }

        GridLayout {
            columns: 2
            Layout.fillWidth: true

            Label {
                text: qsTr("Canton")
                font.italic: true
            }

            Label {
                text: qsTr("NPA")
                font.italic: true
                Layout.alignment: Qt.AlignHCenter
            }

            ComboBox {
                id: cantonField
                textRole: "text"
                valueRole: "npa"
                model: SwissCantons {}
                Layout.minimumWidth: 164
                onActivated: {
                    addressOf.canton = currentText
                    addressOf.zip = currentValue
                }
                displayText: addressOf.canton
                currentIndex: -1
            }

            SpinBox {
                from: 1000
                to: 9999
                editable: true
                value: addressOf.zip
                onValueModified: addressOf.zip = value
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                Layout.maximumWidth: 130
                textFromValue: function(value, locale) {
                    return Number(value).toString();
                }
            }
        }
    }
}
