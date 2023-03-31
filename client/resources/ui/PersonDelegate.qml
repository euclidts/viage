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
        columns: portrait ? 1 : 2

        LabeledTextField {
            id: nameField
            name: qsTr("Nom")
            textOf: model.lastName
            onEdit: function(txt) { model.lastName = txt }
            Layout.maximumWidth: portrait ? window.width
                                          : window.width / 2
        }

        LabeledTextField {
            name: qsTr("Prénom")
            textOf: model.firstName
            onEdit: function(txt) { model.firstName = txt }
        }

        PhoneChooser {
            phoneOf: model
            Layout.maximumWidth: portrait ? window.width
                                          : window.width / 2
        }

        LabeledTextField {
            id: mailField
            name: qsTr("Courriel")
            textOf: model.eMail
            onEdit: function(txt) { model.eMail = txt }
            validator: RegularExpressionValidator {
                regularExpression: /^$|\S+@\S+\.\S+$/
            }
            placeHolder: qsTr("* Champ Nécessaire")
            capitalization: Font.MixedCase
        }
    }
}
