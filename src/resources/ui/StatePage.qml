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
                    id: stateColumn
                    Layout.minimumWidth: 200
                    Layout.margins: 12

                    RoundButton {
                        text: qsTr("Télécharger le document")
                        icon.source: "qrc:/icons/download.svg"
                        highlighted: true
                    }

                    Label {
                        text: qsTr("Etat du Dossier")
                        font.bold: true
                    }

                    CheckBox {
                        id: recieivedCheck
                        text: stateNames[1]
                        checkable: bridge.clearance === 4
                    }

                    CheckBox {
                        id: expertCheck
                        text: stateNames[2]
                        checkable: bridge.clearance === 4
                    }

                    CheckBox {
                        id: decisionCheck
                        text: stateNames[3]
                        checkable: bridge.clearance === 4
                    }

                    CheckBox {
                        id: notaryCheck
                        text: stateNames[4]
                        checkable: bridge.clearance === 4
                    }

                    CheckBox {
                        id: payedCheck
                        text: stateNames[5]
                        checkable: bridge.clearance === 4
                    }

                    function checkStates() {
                        recieivedCheck.checked = bridge.accountHasFlag(32)
                        expertCheck.checked = bridge.accountHasFlag(64)
                        decisionCheck.checked = bridge.accountHasFlag(128)
                        notaryCheck.checked = bridge.accountHasFlag(256)
                        payedCheck.checked = bridge.accountHasFlag(512)
                    }

                    Connections {
                        target: bridge
                        function onAccountStateChanged() {
                            stateColumn.checkStates()
                        }
                    }
                }
            }
        }
    }
}
