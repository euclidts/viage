import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People
import Data

ListView {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    spacing: 6
    clip: true
    boundsBehavior: Flickable.StopAtBounds
    model : selectedUser

    property bool completed: false

    delegate: BackgroundRect {
        id: root

        required property var model
        required property int index

        UserFullDelegate {
            model: root.model
            index: root.index

            RowLayout {
                Layout.margins: 12

                GridLayout {
                    columns: 2

                    Label {
                        text: qsTr("Société")
                        font.italic: true
                    }

                    Label {
                        text: qsTr("Rôle")
                        font.italic: true
                    }

                    ComboBox {
                        editable: true
                        textRole: "name"
                        valueRole: "id"
                        model: CompaniesModel { list: companies }
                        onAccepted: {
                            if (find(editText) === -1)
                                companies.addWith()
                        }
                    }

                    ComboBox {
                        id: clearanceCombo
                        model: clearanceNames
                        Layout.minimumWidth: 180
                        onActivated: root.model.clearance = currentIndex + 1
                        currentIndex: root.model.clearance - 1
                    }
                }

//                IntChooser {
//                    minimum: 1
//                    maximum: 100
//                    name: qsTr("Numéro d'équipe")
//                    numberOf: model.team
//                    onEdit: function(val) { model.team = val }
//                }
            }
        }
    }
}
