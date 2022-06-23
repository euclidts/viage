import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Drawer {
    modal: true
    background.opacity: .8
    height: parent.height
    edge: Qt.RightEdge

    property alias theme: themeSwitch
    property alias invisible: invisibleSwitch

    contentItem: ColumnLayout {
        spacing: 0

        MaterialButton {
            id: invisibleSwitch
            checkable: true
            icon.source: checked ? "qrc:/icons/eye-slash.svg"
                                 : "qrc:/icons/eye.svg"
            text: checked ? qsTr("Mode invisible")
                          : qsTr("Mode visible")
            background.opacity: .0
        }

        MaterialButton {
            id: themeSwitch
            checkable: true
            icon.source: checked ? "qrc:/icons/moon.svg"
                                 : "qrc:/icons/sun.svg"
            text: checked ? qsTr("Thème sombre")
                          : qsTr("Thème clair")
            background.opacity: .0
        }

        GroupBox {
            label: Label {
                text: qsTr("Modification du mot de passe")
                font.italic: true
            }
            Layout.fillWidth: true
            Layout.margins: 12

            ColumnLayout {
                id: newPwdLayout
                width: parent.width

                function validate () {
                    if (validateButton.highlighted) {
                        bridge.updatePwd(newPwd.text)
                        busyDialog.open()
                    }
                }

                PwdField {
                    id: newPwd
                    placeholder: qsTr("Nouveau mot de passe")
                    onFieldAccepted: function () {
                        confirmPwd.text !== "" ? newPwdLayout.validate()
                                               : usernNameField.focus = true
                    }
                }

                PwdField {
                    id: confirmPwd
                    placeholder: qsTr("Nouveau mot de passe")
                    onFieldAccepted: function () {
                        newPwd.text !== "" ? newPwdLayout.validate()
                                           : usernNameField.focus = true
                    }
                }

                RoundButton {
                    id: validateButton
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Valider")
                    highlighted: newPwd.text !== "" && confirmPwd.text !== ""
                    icon.source: "qrc:/icons/checked-square.svg"
                    onClicked: newPwdLayout.validate()
                }
            }
        }

        MaterialButton {
            icon.source: "qrc:/icons/door-open.svg"
            text: qsTr("Déconnection")
            background.opacity: .0
            onClicked: {
                documents.clear()
                exterior.clear()
                habitat.clear()
                contacts.clear()
                owners.clear()
                accounts.clear()
                users.clear()
                settingsDrawer.close()
                rootStack.currentIndex = 0
                logginDialog.open()
            }
        }

        Item { Layout.fillHeight: true }
    }
}
