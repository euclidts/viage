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

    model : InfantModel { list: infants }

    onCountChanged: busyDialog.close()

    property bool completed: infants.completed

    delegate: BackgroundRect {
        id: infant

        required property var model
        required property int index
        property bool editing: true

        InfantDelegate {
            title: qsTr("Enfant")
            width: parent.width
            model: infant.model

            Button {
                id: deleteButton
                icon.source: "qrc:/icons/trash-alt.svg"
                onClicked: infants.removeItems(model.index, model.index)
            }
        }
    }
}
