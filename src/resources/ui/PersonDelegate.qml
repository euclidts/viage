import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ColumnLayout {
    spacing: 12
    Layout.margins: 12
    Layout.minimumWidth: 200

    required property var model

    GridLayout {
        columns: window.width <  400 ? 1 : 2

        LabeledTextField {
            id: nameField
            name: qsTr("Nom")
            textOf: model.lastName
            onEdit: function(txt) { model.lastName = txt }
        }

        LabeledTextField {
            name: qsTr("Prénom")
            textOf: model.firstName
            onEdit: function(txt) { model.firstName = txt }
        }

        LabeledTextField {
            name: qsTr("Téléphone")
            textOf: model.phone
            onEdit: function(txt) { model.phone = txt }
            inputHint: Qt.ImhFormattedNumbersOnly
            validator: RegularExpressionValidator {
                regularExpression: /\d{10,14}?$/
            }
        }

        LabeledTextField {
            name: qsTr("Courriel")
            textOf: model.eMail
            onEdit: function(txt) { model.eMail = txt }
            validator: RegularExpressionValidator {
                regularExpression: /\S+@\S+\.\S+$/
            }
            placeHolder: qsTr("* Champ Nécessaire")
            capitalization: Font.MixedCase
        }
    }
}
