import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Drawer {
    modal: true
    background.opacity: .8
    height: parent.height
    implicitWidth: parent.width - (parent.width / 4)
    edge: Qt.RightEdge
    onClosed: bar.currentIndex = 0

    property alias theme: themeSwitch
    property alias invisible: invisibleSwitch

    contentItem: ColumnLayout {
        width: parent.width

        TabBar {
            id: bar
            Layout.fillWidth: true

            TabButton {
                icon.source: "qrc:/icons/cog.svg"
                text: qsTr("Options")
            }
            TabButton {
                icon.source: "qrc:/icons/user.svg"
                text: qsTr("Profil")
            }
        }

        StackLayout {
            currentIndex: bar.currentIndex

            GridLayout {
                columns: window.width <  400 ? 1 : 2

                MaterialButton {
                    id: themeSwitch
                    checkable: true
                    icon.source: checked ? "qrc:/icons/moon.svg"
                                         : "qrc:/icons/sun.svg"
                    text: checked ? qsTr("Thème sombre")
                                  : qsTr("Thème clair")
                    background.opacity: .0
                }

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
                    icon.source: "qrc:/icons/door-open.svg"
                    text: qsTr("Déconnection")
                    background.opacity: .0
                    onClicked: {
                        logginDialog.close()
                        documents.clear()
                        exterior.clear()
                        habitat.clear()
                        contacts.clear()
                        owners.clear()
                        accounts.clear()
                        users.clear()
                        settingsDrawer.close()
                        logginDialog.open()
                    }
                }
            }

            BackgroundRect {
                ListView {
                    clip: true
                    anchors.fill: parent
                    boundsBehavior: Flickable.StopAtBounds
                    model : currentUser
                    delegate: UserFullDelegate {

                        MaterialButton {
                            text: qsTr("Valider les modifications")
                            icon.source: "qrc:/icons/checked-square.svg"
                            onClicked: users.validate(currentUser.filterRole)
                            Layout.rightMargin: 24
                            Layout.leftMargin: 24
                            Layout.topMargin: -12
                        }

                        GroupBox {
                            Layout.fillWidth: true
                            Layout.rightMargin: 12
                            Layout.leftMargin: 12
                            Layout.bottomMargin: 12

                            ColumnLayout {
                                anchors.fill: parent

                                GridLayout {
                                    Layout.fillWidth: true
                                    columns: window.width <  400 ? 1 : 2

                                    TextField {
                                        id: newPwd
                                        Layout.fillWidth: true
                                        placeholderText: qsTr("Nouveau mot de passe")
                                        echoMode: TextInput.Password
                                    }

                                    TextField {
                                        id: confirmPwd
                                        Layout.fillWidth: true
                                        placeholderText: qsTr("Confirmer le mot de passe")
                                        echoMode: TextInput.Password
                                    }
                                }

                                MaterialButton {
                                    text: qsTr("Valider le nouveau mot de passe")
                                    icon.source: "qrc:/icons/checked-square.svg"
                                    onClicked: if (newPwd.text == confirmPwd.text)
                                                   bridge.updatePwd(newPwd.test, model.id)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
