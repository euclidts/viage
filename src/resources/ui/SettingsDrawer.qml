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

        StackLayout {
            id: settingsStack

            ColumnLayout {
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
                                onExceptionAction("Modification du mot de passe",
                                                  "Êtes-vous sûr de vouloir changer votre mot de passe ?",
                                                  () => {
                                                      busyDialog.open()
                                                      bridge.updatePwd(newPwd.text)
                                                      settingsDrawer.close()
                                                      newPwd.text = ""
                                                      confirmPwd.text = ""
                                                  }, true)
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
                    text: qsTr("Déconnexion")
                    onClicked: {
                        documents.clear()
                        exterior.clear()
                        habitat.clear()
                        contacts.clear()
                        owners.clear()
                        accounts.clear()
                        users.clear()
                        rootStack.currentIndex = 3
                        accountsPages.currentIndex = 0
                        usersPages.currentIndex = 0
                        settingsDrawer.close()
                        logginDialog.open()
                    }
                }

                Item { Layout.fillHeight: true }
            }

            ColumnLayout {
                GroupBox {
                    label: Label {
                        text: qsTr("Crédits")
                        font.italic: true
                    }

                    Layout.margins: 12
                    Layout.fillWidth: true

                    Label {
                        text: "Developped by the Euclid company:
euclidtradingsystems.com
under GNU General Public License v3

Made possible by Qt: qt.io
GNU General Public License v3

Verdigris: github.com/woboq/verdigris
GNU General Public License v3

DuckX: github.com/amiremohamadi/DuckX
MIT License

CMake: cmake.org
BSD 3-clause License"
                    }
                }
            }
        }

        MaterialButton {
            icon.source: settingsStack.currentIndex === 0 ? "qrc:/icons/arrow-right.svg"
                                                          : "qrc:/icons/arrow-left.svg"
            text: settingsStack.currentIndex === 0 ? qsTr("Crédits")
                                                   : qsTr("Options")
            onClicked: settingsStack.currentIndex === 0 ? settingsStack.currentIndex = 1
                                                        : settingsStack.currentIndex = 0
        }
    }
}
