import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool editing: true

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                spacing: 12

                Label {
                    Layout.margins: 6
                    text: qsTr("Conseiller ") + (currentUser.index + 1)
                    font.bold: true
                }

                PersonDelegate {
                    Layout.margins: 12
                    Layout.fillWidth: true
                    model: currentUser

                    LabeledTextField {
                        name: qsTr("Sosciete")
                        textOf: currentUser.company
                        canEdit: editing
                        onEdit: function(txt) { currentUser.company = txt }
                    }

                    Label {
                        text: qsTr("Rôle")
                        font.italic: true
                    }

                    ComboBox {
                        id: clearanceCombo
                        visible: editing
                        model: [
                            qsTr("vendeur"),
                            qsTr("manager"),
                            qsTr("administrateur")
                        ]
                        Layout.minimumWidth: 180
                        onActivated: currentUser.clearance = currentIndex
                        currentIndex: currentUser.clearance
                    }

                    TextField {
                        text: clearanceCombo.model[currentUser.clearance]
                        readOnly: true
                        visible: !editing
                        Layout.fillWidth: true
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
                        canEdit: editing
                        onEdit: function(txt) { currentUser.beneficiary = txt }
                    }

                    LabeledTextField {
                        name: qsTr("Iban")
                        textOf: currentUser.iban
                        canEdit: editing
                        onEdit: function(txt) { currentUser.iban = txt }
                    }

                    LabeledTextField {
                        name: qsTr("SWIFT/BIC")
                        textOf: currentUser.bic
                        canEdit: editing
                        onEdit: function(txt) { currentUser.bic = txt }
                    }

                    AddressChooser {
                        addressOf: currentUser
                        canEdit: editing
                    }

                    Button {
                        text: qsTr("Modifier")
                        highlighted: true
                        Layout.alignment: Qt.AlignRight
                        visible: !editing
                        onClicked: editing = true
                    }

                    Button {
                        id: validateButton
                        highlighted: true
                        text: qsTr("Valider")
                        Layout.alignment: Qt.AlignRight
                        visible: editing
                        onClicked:
                            //                if (!foucsOnEmpty())
                        {
                            editing = false
                            users.validate(currentUser.index)
                        }
                    }
                }

                //    onCompleted: {
                //        if (currentAccount.state > 3) {
                //            editing = false
                //            completed = true
                //        }

                //        contentItem.contentY = this.y
                //    }
            }
        }
    }
}
