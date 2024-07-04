import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Button {
    id: rooot

    property bool fillWidth: true

    flat: true
    Layout.fillWidth: fillWidth
    display: AbstractButton.TextBesideIcon
}
