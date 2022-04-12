import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Dialog {
    modal: true
    closePolicy: Popup.NoAutoClose
    background.opacity: .8

    property string currentState: "ready"

    contentItem: Column {
        id: credentialsEditors
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
//                onAccepted: companyField.focus = true
                onAccepted: validationButton.focus = true
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

//        ComboBox {
//            id: companyField
//            width: parent.width
//            background.opacity: 0.

//            model: ListModel {
//                id: companies
//                ListElement { text: qsTr("Societe 1") }
//                ListElement { text: qsTr("Societe 2") }
//                ListElement { text: qsTr("Societe 3") }
//            }
//        }

        Button {
            id: validationButton
            text: qsTr("Valider")
            width: parent.width
            font.capitalization: Font.MixedCase
            font.bold: true
            highlighted: true
            anchors.bottomMargin: 2
            onClicked: {
                currentState = "authenticating"
                bridge.authenticate(usernNameField.text,
                                    passwordField.text)
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: currentState == "authenticating"
            anchors.horizontalCenter: parent.horizontalCenter
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

