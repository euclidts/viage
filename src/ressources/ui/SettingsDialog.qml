import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Dialog {
    modal: true
    background.opacity: .8

    property alias theme: themeSwitch
    property alias invisible: invisibleSwitch

    contentItem: Column {
        id: credentialsEditors
        Layout.fillWidth: true
        spacing: 0

        Switch {
            id: themeSwitch
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Theme sombre / clair")
        }

        Switch {
            id: invisibleSwitch
            width: parent.width
            checked: true
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Mode invisible")
        }
    }
}
