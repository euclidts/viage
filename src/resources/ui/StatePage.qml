import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                Layout.minimumWidth: 200

                ColumnLayout {
                    Layout.minimumWidth: 200
                    Layout.margins: 12

                    Label {
                        text: qsTr("Etat du Dossier")
                        font.bold: true
                    }

                    CheckBox {
                        checked: hasFlag(currentAccount.state, 32)
                        text: stateNames[1]
                        checkable: !checked
                    }

                    CheckBox {
                        checked: hasFlag(currentAccount.state, 64)
                        text: stateNames[2]
                        checkable: !checked
                    }

                    CheckBox {
                        checked: hasFlag(currentAccount.state, 128)
                        text: stateNames[3]
                        checkable: !checked
                    }
                }
            }
        }
    }
}
