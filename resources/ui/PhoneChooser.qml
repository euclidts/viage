import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ColumnLayout {
    spacing: 12

    required property var phoneOf
    property int capitalization: Font.Capitalize

    Label {
        id: label
        Layout.topMargin: 6
        text: qsTr("Téléphone")
        font.italic: true
    }

    RowLayout {
        Layout.topMargin: -6
        ComboBox {
            id: codeBox
            Layout.maximumWidth: 90

            model: ListModel {
                ListElement {
                    text: "SUI"
                    code: "+41"
                }
                ListElement {
                    text: "FRA"
                    code: "+33"
                }
                ListElement {
                    text: "DEU"
                    code: "+49"
                }
                ListElement {
                    text: "ITA"
                    code: "+39"
                }
            }
            textRole: "text"
            valueRole: "code"
            Component.onCompleted: currentIndex = indexOfValue(phoneOf.phone.slice(0, 3))
            onActivated: { phoneOf.phone = currentValue + field.text }
        }

        TextField {
            id: codeField
            Layout.maximumWidth: 60
            readOnly: true
            text: phoneOf.phone.slice(0, 3)
        }

        TextField {
            id: field
            readonly property string number: phoneOf.phone
            text: number.slice(3, number.length)
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            Layout.fillWidth: true
            placeholderText: qsTr("* Champ obligatoire")
            onAccepted: focus = false
            validator: RegularExpressionValidator {
                regularExpression: /^$|\d{9,13}?$/
            }
            onTextChanged: if (acceptableInput) {
                               color = Material.foreground
                               phoneOf.phone = codeField.text + text
                           } else color = "red"
        }
    }
}
