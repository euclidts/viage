import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Button {
    id: rooot
    Layout.fillWidth: true
    display: AbstractButton.TextBesideIcon
    background: Rectangle {
        implicitHeight: Material.buttonHeight
        radius: 2
        color: Material.backgroundColor

        Ripple {
            clipRadius: 2
            width: parent.width
            height: parent.height
            pressed: rooot.pressed
            anchor: rooot
            color: rooot.flat && rooot.highlighted ? Material.highlightedRippleColor
                                                         : Material.rippleColor
        }
    }
}
