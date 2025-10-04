import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

ColumnLayout {
    id: root
    property int sex: 0  // valeur initiale

    ButtonGroup {
        id: sexGroup
        buttons: sexRow.children

        onCheckedButtonChanged: {
            sex = checkedButton.index
        }
    }

    RowLayout {
        id: sexRow
        spacing: 0
        Layout.margins: 0

        RadioButton {
            id: maleButton
            text: qsTr("Monsieur")
            readonly property int index: 0
            checked: sex === index
        }

        RadioButton {
            id: femaleButton
            text: qsTr("Madame")
            readonly property int index: 1
            checked: sex === index
        }
    }
}
/*
ColumnLayout {
    id: root
    property int sex: 0
    ButtonGroup {
        id: sexGroup
        buttons: sexRow.children

        onCheckedButtonChanged: {
            sex = checkedButton.index
        }
    }

    RowLayout {
        id: sexRow
        spacing: 0
        Layout.margins: 0

        RadioButton {
            id: maleButton
            text: qsTr("Monsieur")
            readonly property int index: 0
        }

        RadioButton {
            id: femaleButton
            text: qsTr("Madame")
            readonly property int index: 1
        }
    }

    mpleted: {
        // Initialise le bouton correct au démarrage
        let current = sex
        if (current === 0)
            sexGroup.checkButton(maleButton)
        else if (current === 1)
            sexGroup.checkButton(femaleButton)
    }
}
*/
