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
                    text: qsTr("Conseiller ") + (currentAdvisor.index + 1)
                    font.bold: true
                }

                PersonDelegate {
                    Layout.margins: 12
                    Layout.fillWidth: true
                    model: currentAdvisor

                    LabeledTextField {
                        name: qsTr("Sosciete")
                        textOf: currentAdvisor.company
                        canEdit: editing
                        onEdit: function(txt) { currentAdvisor.company = txt }
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
                        onActivated: currentAdvisor.clearance = currentIndex
                        currentIndex: currentAdvisor.clearance
                    }

                    TextField {
                        text: clearanceCombo.model[currentAdvisor.clearance]
                        readOnly: true
                        visible: !editing
                        Layout.fillWidth: true
                    }

                    IntChooser {
                        minimum: 1
                        maximum: 100
                        name: qsTr("Numéro d'équipe")
                        numberOf: currentAdvisor.team
                        onEdit: function(val) { currentAdvisor.team = val }
                    }

                    LabeledTextField {
                        name: qsTr("Bénéficiaire du compte")
                        textOf: currentAdvisor.beneficiary
                        canEdit: editing
                        onEdit: function(txt) { currentAdvisor.beneficiary = txt }
                    }

                    LabeledTextField {
                        name: qsTr("Iban")
                        textOf: currentAdvisor.iban
                        canEdit: editing
                        onEdit: function(txt) { currentAdvisor.iban = txt }
                    }

                    LabeledTextField {
                        name: qsTr("SWIFT/BIC")
                        textOf: currentAdvisor.bic
                        canEdit: editing
                        onEdit: function(txt) { currentAdvisor.bic = txt }
                    }

                    AddressChooser {
                        addressOf: currentAdvisor
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
                            advisors.validate(currentAdvisor.index)
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
