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
                Layout.margins: 12

                GridLayout {
                    id: stateColumn
                    columns: 2
                    Layout.minimumWidth: 200
                    Layout.margins: 12

                    Label {
                        Layout.leftMargin: -6
                        text: qsTr("Etat du Dossier")
                        font.bold: true
                    }

                    CheckBox {
                        id: recieivedCheck
                        text: stateNames[7]
                        checkable: bridge.clearance === 4
                        onCheckStateChanged: {}
                    }

                    Label {
                        text: Qt.formatDate(bridge.accountReceived, "dd.MM.yy")
                        visible: recieivedCheck.checked && text !== ""
                    }

                    CheckBox {
                        id: expertCheck
                        text: stateNames[8]
                        checkable: bridge.clearance === 4
                    }

                    Label {
                        text: Qt.formatDate(bridge.accountExpertized, "dd.MM.yy")
                        visible: expertCheck.checked && text !== ""
                    }

                    CheckBox {
                        id: decisionCheck
                        text: stateNames[9]
                        checkable: bridge.clearance === 4
                    }

                    Label {
//                        text: Qt.formatDate(bridge.accountNotarized, "dd.MM.yy")
                        visible: decisionCheck.checked && text !== ""
                    }

                    CheckBox {
                        id: notaryCheck
                        text: stateNames[10]
                        checkable: bridge.clearance === 4
                    }

                    Label {
                        text: Qt.formatDate(bridge.accountNotarized, "dd.MM.yy")
                        visible: notaryCheck.checked && text !== ""
                    }

                    CheckBox {
                        id: payedCheck
                        text: stateNames[11]
                        checkable: bridge.clearance === 4
                    }

                    Label {
                        text: Qt.formatDate(bridge.accountPaid, "dd.MM.yy")
                        visible: payedCheck.checked && text !== ""
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

                    RoundButton {
                        text: qsTr("Télécharger le document")
                        icon.source: "qrc:/icons/download.svg"
                        highlighted: true
                    }
                }
            }
        }
    }
}
