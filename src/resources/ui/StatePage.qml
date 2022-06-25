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
                id: stateColumn
                width: parent.width
                Layout.minimumWidth: 200

                Label {
                    text: qsTr("Etat du Dossier")
                    font.bold: true
                    Layout.margins: 12
                }

                StateLayout {
                    id: recieivedCheck
                    nameIndex: 7
                    date: bridge.accountReceived
                }

                StateLayout {
                    id: expertCheck
                    nameIndex: 8
                    date: bridge.accountExpertized
                }

                StateLayout {
                    id: decidedCheck
                    nameIndex: 9
                    date: bridge.accountDecided
                }

                StateLayout {
                    id: notaryCheck
                    nameIndex: 10
                    date: bridge.accountNotarized
                }

                StateLayout {
                    id: payedCheck
                    nameIndex: 11
                    date: bridge.accountPaid
                }

                function checkStates() {
                    recieivedCheck.flagged = bridge.accountHasFlag(32)
                    expertCheck.flagged = bridge.accountHasFlag(64)
                    decidedCheck.flagged = bridge.accountHasFlag(128)
                    notaryCheck.flagged = bridge.accountHasFlag(256)
                    payedCheck.flagged = bridge.accountHasFlag(512)
                }

                Connections {
                    target: bridge
                    function onAccountStateChanged() {
                        stateColumn.checkStates()
                    }
                }

                RoundButton {
                    text: qsTr("Télécharger le document")
                    icon.source: "qrc:/icons/download.svg"
                    highlighted: true
                }
            }
        }
    }
}
