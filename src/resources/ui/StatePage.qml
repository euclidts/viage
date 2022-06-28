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
                    nameIndex: 6
                }

                StateLayout {
                    id: expertCheck
                    nameIndex: 7
                }

                StateLayout {
                    id: decidedCheck
                    nameIndex: 8
                }

                StateLayout {
                    id: notaryCheck
                    nameIndex: 9
                }

                StateLayout {
                    id: paidCheck
                    nameIndex: 10
                }

                function checkStates() {
                    recieivedCheck.flagged = bridge.accountHasFlag(32)
                    recieivedCheck.validation = bridge.accountReceived

                    expertCheck.flagged = bridge.accountHasFlag(64)
                    expertCheck.validation = bridge.accountExpertized

                    decidedCheck.flagged = bridge.accountHasFlag(128)
                    decidedCheck.validation = bridge.accountDecided

                    notaryCheck.flagged = bridge.accountHasFlag(256)
                    notaryCheck.validation = bridge.accountNotarized

                    paidCheck.flagged = bridge.accountHasFlag(512)
                    paidCheck.validation = bridge.accountPaid
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
