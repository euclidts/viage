import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: users.completed

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                spacing: 12

                PersonDelegate {
                    Layout.margins: 12
                    Layout.fillWidth: true
                    model: currentUser

                    LabeledTextField {
                        name: qsTr("Société")
                        textOf: currentUser.company
                        onEdit: function(txt) { currentUser.company = txt }
                    }

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
                        onActivated: currentUser.clearance = currentIndex
                        currentIndex: currentUser.clearance
                    }

                    IntChooser {
                        minimum: 1
                        maximum: 100
                        name: qsTr("Numéro d'équipe")
                        numberOf: currentUser.team
                        onEdit: function(val) { currentUser.team = val }
                    }

                    LabeledTextField {
                        name: qsTr("Bénéficiaire du compte")
                        textOf: currentUser.beneficiary
                        onEdit: function(txt) { currentUser.beneficiary = txt }
                    }

                    LabeledTextField {
                        name: qsTr("Iban")
                        textOf: currentUser.iban
                        onEdit: function(txt) { currentUser.iban = txt }
                    }

                    LabeledTextField {
                        name: qsTr("SWIFT/BIC")
                        textOf: currentUser.bic
                        onEdit: function(txt) { currentUser.bic = txt }
                    }

                    AddressChooser {
                        addressOf: currentUser
                    }
                }
            }
        }
    }
}
