import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

GroupBox {
    id: root
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var addressOf

    label: Label {
        text: qsTr("Adresse")
        font.italic: true
    }

    ColumnLayout {
        spacing: 12
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

        RowLayout {
            Layout.fillWidth: true

            ColumnLayout {

                Label {
                    text: qsTr("Canton")
                    font.italic: true
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
            }

            IntChooser {
                name: qsTr("NPA")
                maxSize: 150
                minimum: 1000
                maximum: 9999
                numberOf: addressOf.zip
                onEdit: (val) => { addressOf.zip = val }
                spin.textFromValue: (value, locale) => {
                    return Number(value).toString();
                }
            }

//            SpinBox {
//                from: 1000
//                to: 9999
//                editable: true
//                value: addressOf.zip
//                onValueModified: addressOf.zip = value
//                inputMethodHints: Qt.ImhFormattedNumbersOnly
//                Layout.maximumWidth: 130
//                textFromValue: function(value, locale) {
//                    return Number(value).toString();
//                }
//            }
        }
    }
}
