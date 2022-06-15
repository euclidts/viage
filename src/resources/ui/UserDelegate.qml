import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

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

            Label { text: model.company }

            Label { text: qsTr("Equipe ") + model.team }
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
            spacing: 0

            Item { Layout.preferredWidth: parent.width - 220 }

            RoundButton {
                icon.source: "qrc:/icons/door-open.svg"
            }

            RoundButton {
                icon.source: "qrc:/icons/times-circle.svg"
            }
        }
    }

    Component.onCompleted: {
        currentUser = model
        if (hiring) {
            hiring = false
            usersPages.currentIndex = 1
            users.loadFrom(model.id)
        }
    }

    onClicked: {
        selectedUser.filterRole = model.id
        usersPages.currentIndex = 1
    }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: Material.background
        opacity: .8
    }
}
