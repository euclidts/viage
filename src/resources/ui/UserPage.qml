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
        id: selectedUserDelegate

        required property var model
        required property int index

        ColumnLayout {
            id: root
            spacing: 0
            width: parent.width
            Layout.minimumWidth: 200
            Layout.margins: 6

            PersonDelegate {
                Layout.margins: 12
                Layout.fillWidth: true
                model: selectedUserDelegate.model

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
                            model: [
                                qsTr("vendeur"),
                                qsTr("manager"),
                                qsTr("administrateur")
                            ]
                            Layout.minimumWidth: 180
                            onActivated: selectedUserDelegate.model.clearance = currentIndex
                            currentIndex: selectedUserDelegate.model.clearance
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

                LabeledTextField {
                    name: qsTr("Bénéficiaire du compte")
                    textOf: model.beneficiary
                    onEdit: function(txt) { model.beneficiary = txt }
                }

                LabeledTextField {
                    name: qsTr("Iban")
                    textOf: model.iban
                    onEdit: function(txt) { model.iban = txt }
                }

                LabeledTextField {
                    name: qsTr("SWIFT/BIC")
                    textOf: model.bic
                    onEdit: function(txt) { model.bic = txt }
                }

                AddressChooser {
                    addressOf: model
                }
            }
        }
    }
}
