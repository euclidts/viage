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
            visible: rootStack.currentIndex == 0 && accountsPages.currentIndex == 0
            checkable: true
            icon.source: checked ? "qrc:/icons/eye-slash.svg"
                                 : "qrc:/icons/eye.svg"
            text: checked ? qsTr("Mode invisible")
                          : qsTr("Mode visible")
        }

        MaterialButton {
            id: themeSwitch
            checkable: true
            icon.source: checked ? "qrc:/icons/moon.svg"
                                 : "qrc:/icons/sun.svg"
            text: checked ? qsTr("Thème sombre")
                          : qsTr("Thème clair")
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
                    icon.source: "qrc:/icons/check-square.svg"
                    onClicked: newPwdLayout.validate()
                }
            }
        }

        MaterialButton {
            icon.source: "qrc:/icons/door-open.svg"
            text: qsTr("Déconnection")
            onClicked: {
                documents.clear()
                exterior.clear()
                habitat.clear()
                contacts.clear()
                owners.clear()
                accounts.clear()
                users.clear()
                topBar.visible = false
                bottomBar.visible = false
                settingsDrawer.close()
                rootStack.currentIndex = 0
                logginDialog.open()
            }
        }

        Item { Layout.fillHeight: true }
    }
}
