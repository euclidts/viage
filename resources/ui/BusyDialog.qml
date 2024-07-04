import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Dialog {
    modal: true
    closePolicy: Popup.NoAutoClose
    background.opacity: 0
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)

    BusyIndicator {
        anchors.fill: parent
    }
}

