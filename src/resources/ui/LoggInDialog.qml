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

    property string currentState: "ready"

    function validate() {
        currentState = "authenticating"
        bridge.authenticate(usernNameField.text,
                            passwordField.text)
        busyDialog.open()
    }

    contentItem: Column {
        spacing: 15

        Image {
            id: logo
            source: "qrc:/images/ViageLogo.svg"
            width: parent.width
            fillMode: Image.PreserveAspectFit
        }

        TextField {
            id: usernNameField
            width: parent.width
            placeholderText: qsTr("Nom d'utilisateur")
            text: ""
            onAccepted: passwordField.focus = true
        }

        RowLayout {
            width: parent.width
            spacing: 0

            TextField {
                id: passwordField
                Layout.fillWidth: true
                placeholderText: qsTr("Mot de passe")
                text: ""
                echoMode: TextInput.Password
                onAccepted: usernNameField.text !== "" ? validate()
                                                      : usernNameField.focus = true
            }

            Button {
                id: echoSwitch
                flat: true
                checkable: true
                icon.source: "qrc:/icons/eye.svg"
                Layout.alignment: Qt.AlignLeft
                background: Rectangle {
                    radius: 2
                    color: Material.buttonDisabledColor

                    PaddedRectangle {
                        y: passwordField.height - height - passwordField.bottomPadding + 3
                        width: parent.width
                        height: passwordField.activeFocus || passwordField.hovered ? 2 : 1
                        color: passwordField.activeFocus ? Material.accentColor
                                                   : (passwordField.hovered ? Material.primaryTextColor : Material.hintTextColor)
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

                onClicked: if (checked) {
                               passwordField.echoMode = TextInput.Normal;
                               this.icon.source = "qrc:/icons/eye-slash.svg";
                           } else {
                               passwordField.echoMode = TextInput.Password;
                               this.icon.source = "qrc:/icons/eye.svg";
                           }
            }
        }

        Button {
            id: validationButton
            text: qsTr("Valider")
            width: parent.width
            font.capitalization: Font.MixedCase
            font.bold: true
            highlighted: true
            anchors.bottomMargin: 2
            onClicked: validate()
        }

        Label {
            id: errorLabel
            visible: currentState == "error"
            text: qsTr("Erreur d'authentification")
            color: "red"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

