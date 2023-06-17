import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ListView {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    spacing: 6
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    model : ContactModel { list: contacts }

    onCountChanged: busyDialog.close()

    property bool completed: contacts.completed

    delegate: BackgroundRect {
        id: contact

        required property var model
        required property int index

        ContactDelegate {
            id: root
            title: qsTr("Contact")
            width: parent.width
            model: contact.model

            RoundButton {
                icon.source: "qrc:/icons/trash-alt.svg"
                text: qsTr("Supprimer le ") + root.title
                onClicked: contacts.remove(model.id)
            }
        }
    }
}
