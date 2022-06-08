import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

InfantDelegate {

    CheckBox {
        text: qsTr("Enfant de propriétaire")
        checked: model.isInfant
        onCheckStateChanged: model.isInfant = checked
    }

}
