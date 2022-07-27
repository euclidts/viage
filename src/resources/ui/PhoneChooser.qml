import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ColumnLayout {
    spacing: 0

    required property var phoneOf
    property int capitalization: Font.Capitalize

    Label {
        id: label
        text: qsTr("Téléphone")
        font.italic: true
    }

    RowLayout {
        Layout.fillWidth: true

        ComboBox {
            id: codeBox
            Layout.maximumWidth: 90

            model: ListModel {
                ListElement {
                    text: ""
                    code: "+??"
                }
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
            Layout.maximumWidth: 40
            readOnly: codeBox.currentIndex > 0
            text: phoneOf.phone.slice(0, 3)
        }

        TextField {
            id: field
            text: phoneOf.phone.slice(3, phoneOf.phone.length)
            onEditingFinished: phoneOf.phone = codeField.text + text
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            placeholderText: qsTr("* Champ Obligatoire")
            Layout.fillWidth: true
            onAccepted: focus = false
            validator: RegularExpressionValidator {
                regularExpression: /\d{9,13}?$/
            }
            onTextChanged: acceptableInput ? color = Material.foreground
                                           : color = "red"
        }
    }
}
