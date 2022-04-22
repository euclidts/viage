import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: false

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
                        checked: currentAccount.state >= 32
                        onCheckStateChanged: exterior.parking = checked
                        text: stateNames[1]
                        checkable: currentAccount.state < 32
                    }

                    CheckBox {
                        checked: currentAccount.state >= 64
                        onCheckStateChanged: exterior.parking = checked
                        text: stateNames[2]
                        checkable: currentAccount.state < 32
                    }

                    CheckBox {
                        checked: currentAccount.state >= 32
                        onCheckStateChanged: exterior.parking = checked
                        text: stateNames[3]
                        checkable: editing
                    }
                }
            }
        }
    }
}
