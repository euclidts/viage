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
    property bool editing: true

//    function foucsOnEmpty() {
//        if (nameField.text === "") {
//            nameField.focus = true
//            contentItem.contentY = nameField.y
//        } else if (surNameField.text === "") {
//            surNameField.focus = true
//            contentItem.contentY = surNameField.y
//        } else if (phoneNumberField.text === "") {
//            phoneNumberField.focus = true
//            contentItem.contentY = phoneNumberField.y
//        }
//    }

    LabeledTextField {
        id: nameField
        name: qsTr("Nom")
        textOf: model.lastName
        canEdit: editing
        onEdit: function(txt) { model.lastName = txt }
    }

    LabeledTextField {
        name: qsTr("Prénom")
        textOf: model.firstName
        canEdit: editing
        onEdit: function(txt) { model.firstName = txt }
    }

    LabeledTextField {
        name: qsTr("Téléphone")
        textOf: model.phone
        canEdit: editing
        onEdit: function(txt) { model.phone = txt }
        inputHint: Qt.ImhFormattedNumbersOnly
        validator: RegularExpressionValidator {
            regularExpression: /\d{10,14}?$/
        }
    }

    LabeledTextField {
        name: qsTr("Couriel")
        textOf: model.eMail
        canEdit: editing
        onEdit: function(txt) { model.eMail = txt }
        validator: RegularExpressionValidator {
            regularExpression: /\S+@\S+\.\S+$/
        }
    }
}
