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
    model : selectedUser
    delegate: BackgroundRect {
        id: root

        required property var model
        required property int index

        UserFullDelegate {
            model: root.model
            index: root.index

            LabeledTextField {
                name: qsTr("Société")
                textOf: model.company
                onEdit: function(txt) { model.company = txt }
            }

            RowLayout {
                ColumnLayout {
                    Label {
                        text: qsTr("Rôle")
                        font.italic: true
                    }

                    ComboBox {
                        id: clearanceCombo
                        model: bridge.clearance === 4
                               ? [qsTr("vendeur"),
                                  qsTr("manager"),
                                  qsTr("directeur"),
                                  qsTr("administrateur")]
                               : [qsTr("vendeur"),
                                  qsTr("manager"),
                                  qsTr("directeur")]
                        Layout.minimumWidth: 180
                        onActivated: root.model.clearance = currentIndex
                        currentIndex: root.model.clearance
                    }
                }

                IntChooser {
                    minimum: 1
                    maximum: 100
                    name: qsTr("Numéro d'équipe")
                    numberOf: model.team
                    onEdit: function(val) { model.team = val }
                }
            }
        }
    }
}
