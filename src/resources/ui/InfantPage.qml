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

    property bool completed: false

    onCountChanged: busyDialog.close()

    delegate: BackgroundRect {
        id: infant

        required property var model
        required property int index
        property bool editing: true

        onVisibleChanged: if (visible) checkCompleted()

        function checkCompleted() {

            if (model.name === "") {
                infantPage.completed = false
                return
            } else if (model.surname === "") {
                infantPage.completed = false
                return
            } else if (model.phone === "") {
                infantPage.completed = false
                return
            }

            infantPage.completed = true
        }

        Connections {
            target: infantPage.model
            function onDataChanged(topLeft, bottomRight, roles) {
                if (topLeft.row === model.index) {
                    infant.checkCompleted()
                }
            }
        }

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
