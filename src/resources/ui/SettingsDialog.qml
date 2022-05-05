import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Dialog {
    modal: true
    background.opacity: .8
    x: Math.round((parent.width - width) / 2)
    y: 120
    implicitWidth: 270

    property alias theme: themeSwitch
    property alias invisible: invisibleSwitch

    contentItem: Column {
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
