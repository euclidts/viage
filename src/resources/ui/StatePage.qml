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
                    expertCheck.flagged = bridge.accountHasFlag(64)
                    decidedCheck.flagged = bridge.accountHasFlag(128)
                    notaryCheck.flagged = bridge.accountHasFlag(256)
                    paidCheck.flagged = bridge.accountHasFlag(512)
                }

                Connections {
                    target: bridge
                    function onAccountStateChanged() {
                        stateColumn.checkStates()
                    }
                }

                Connections {
                    target: bridge
                    function onAccountReceivedChanged() {
                        recieivedCheck.validation = bridge.accountReceived
                    }
                }

                Connections {
                    target: bridge
                    function onAccountExpertizedChanged() {
                        expertCheck.validation = bridge.accountExpertized
                    }
                }

                Connections {
                    target: bridge
                    function onAccountNotarizedChanged() {
                        notaryCheck.validation = bridge.accountNotarized
                    }
                }

                Connections {
                    target: bridge
                    function onAccountDecidedChanged() {
                        decidedCheck.validation = bridge.accountDecided
                    }
                }

                Connections {
                    target: bridge
                    function onAccountPaidChanged() {
                        paidCheck.validation = bridge.accountPaid
                    }
                }

                RoundButton {
                    text: qsTr("Télécharger le document")
                    icon.source: "qrc:/icons/download.svg"
                    highlighted: true
                    onClicked: {
                        busyDialog.open()
                        bridge.sendOnboardedEmail()
                    }
                }
            }
        }
    }
}
