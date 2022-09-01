import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import People

ItemDelegate {
    width: window.width
    leftInset: 6
    rightInset: 6
    topInset: 3
    bottomInset: 3

    contentItem: RowLayout {

        ColumnLayout {
            Layout.preferredWidth: window.width / 3

            Label {
                text: model.company
                font.bold: true
            }

            Label {
                text: qsTr("Équipe ") + model.team
                font.italic: true
            }
        }

        ColumnLayout {
            Layout.preferredWidth: window.width / 3

            Label {
                text: model.firstName + ' ' + model.lastName
                font.bold: true
                font.capitalization: Font.Capitalize
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
            Layout.preferredWidth: window.width / 3

            Item { Layout.fillWidth: true }

            RoundButton {
                icon.source: "qrc:/icons/door-open.svg"
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Renvoyer de nouveaux identifiants")
                onClicked: onExceptionAction(ToolTip.text,
                                         "Le mot de passe actuelle de l'utilisateur séléctioné sera perdu",
                                         () => {
                                             bridge.resetPwd(model.id)
                                             busyDialog.open()
                                         }, true)
            }

            RoundButton {
                icon.source: model.isLocked ? "qrc:/icons/lock-open.svg"
                                            : "qrc:/icons/lock.svg"
                ToolTip.visible: hovered
                ToolTip.text: model.isLocked ? qsTr("Rependre l'activité")
                                             : qsTr("Suspendre l'activité")
                onClicked: onExceptionAction(ToolTip.text,
                                         model.isLocked ? qsTr("L'utilisatuer séléctioné pourra de nouveau se connecter")
                                                        : qsTr("L'utilisatuer séléctioné ne pourra plus se connecter"),
                                         () => {
                                             model.isLocked = !model.isLocked
                                             users.validate(model.id)
                                         }, true)
            }
        }
    }

    onClicked: { selectedUser.forceFilterRole(model.id) }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: model.isLocked ? Material.color(Material.purle) : Material.background
        opacity: .8
    }
}
