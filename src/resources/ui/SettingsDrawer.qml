import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Drawer {
    modal: true
    background.opacity: .8
    height: parent.height
    implicitWidth: parent.width - 24
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

            ColumnLayout {
                MaterialButton {
                    id: themeSwitch
                    checkable: true
                    icon.source: checked ? "qrc:/icons/moon.svg"
                                         : "qrc:/icons/sun.svg"
                    text: checked ? qsTr("Theme sombre")
                                  : qsTr("Theme clair")
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
            }

            ListView {
                clip: true
                boundsBehavior: Flickable.StopAtBounds
                model : currentUser
                delegate: UserFullDelegate {}
            }
        }
    }
}
