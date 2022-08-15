import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Interface

ColumnLayout {
    id: root
    spacing: 0
    width: parent.width
    Layout.minimumWidth: 200
    Layout.margins: 6

    required property var model
    required property int index

    PersonDelegate {
        Layout.margins: 12
        Layout.fillWidth: true
        model: root.model

        GridLayout {
            columns: portrait ? 1 : 2

            LabeledTextField {
                name: qsTr("Bénéficiaire du compte")
                textOf: model.beneficiary
                onEdit: function(txt) { model.beneficiary = txt }
                Layout.maximumWidth: portrait ? window.width
                                              : window.width / 2
            }

            LabeledTextField {
                name: qsTr("Iban")
                textOf: model.iban
                onEdit: function(txt) { model.iban = txt }
            }
        }

        LabeledTextField {
            name: qsTr("SWIFT/BIC")
            textOf: model.bic
            onEdit: function(txt) { model.bic = txt }
        }

        AddressChooser {
            addressOf: model
        }

        Connections {
            target: model
            function onCompletedChanged() {
                userPage.completed = model.completed
            }
        }

        Component.onCompleted: userPage.completed = model.completed
    }
}
