import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Dialog {
    modal: true
    closePolicy: Popup.NoAutoClose
    background.opacity: .8
    x: Math.round((parent.width - width) / 2)
    y: 120
    implicitWidth: 270

    function validate() {
        bridge.authenticate(usernNameField.text,
                            passwordField.text)
        logginDialog.close()
        busyDialog.open()
    }

    function clear() { passwordField.text = "" }

    contentItem: ColumnLayout {
        spacing: 15

        Image {
            id: logo
            source: "qrc:/images/ViageLogo.svg"
            Layout.fillWidth: true
            Layout.preferredHeight: width
            fillMode: Image.PreserveAspectFit
        }

        TextField {
            id: usernNameField
            Layout.fillWidth: true
            placeholderText: qsTr("Nom d'utilisateur")
            onAccepted: passwordField.text !== "" ? validate()
                                                   : passwordField.fieldFocus = true
        }

        PwdField {
            id: passwordField
            onFieldAccepted: function () {
                usernNameField.text !== "" ? validate()
                                           : usernNameField.focus = true
            }
        }

        RoundButton {
            id: validationButton
            icon.source: "qrc:/icons/door-open.svg"
            text: qsTr("Valider")
            Layout.fillWidth: true
            font.capitalization: Font.MixedCase
            font.bold: true
            highlighted: passwordField.text !== "" && usernNameField.text !== ""
            onClicked: if (passwordField.text !== "" && usernNameField.text !== "")
                           validate()
        }
    }
}

