import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import People

ItemDelegate {
    width: parent.width
    leftInset: 6
    rightInset: 6
    topInset: 3
    bottomInset: 3

    contentItem: RowLayout {
        width: parent.width

        ColumnLayout {
            Layout.preferredWidth: parent.width / 3

            Label {
                text: model.company
                font.bold: true
            }

            Label {
                text: qsTr("Equipe ") + model.team
                font.italic: true
            }
        }

        ColumnLayout {
            Layout.preferredWidth: parent.width / 3

            Label {
                text: model.firstName + ' ' + model.lastName
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                text: clearanceNames[model.clearance - 1]
                font.italic: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width / 3

            Item { Layout.fillWidth: true }

            RoundButton {
                icon.source: "qrc:/icons/door-open.svg"
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Renvoyer de nouveaux identifiants")
                onClicked: {
                    bridge.resetPwd(model.id)
                    busyDialog.open()
                }
            }

            RoundButton {
                Layout.rightMargin: 24
                icon.source: model.isLocked ? "qrc:/icons/lock-open.svg"
                                            : "qrc:/icons/lock.svg"
                ToolTip.visible: hovered
                ToolTip.text: model.isLocked ? qsTr("Rependre l'activité")
                                             : qsTr("Suspendre l'activité")
                onClicked: {
                    model.isLocked = !model.isLocked
                    users.validate(model.id)
                }
            }
        }
    }

    onClicked: { selectedUser.forceFilterRole(model.id) }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: model.isLocked ? Material.color(Material.Amber) : Material.background
        opacity: .8
    }
}
