import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import Data
import Places
import Interface

ItemDelegate {
    width: parent.width
    leftInset: 6
    rightInset: 6
    topInset: 3
    bottomInset: 3

    contentItem: RowLayout {
        id: accountRow

        ColumnLayout {
            Layout.fillWidth: true

            Label {
                text: Qt.formatDateTime(created, "dd.MM.yy")
                      + " - " + acronym
            }

            Label {
                id: stateLabel
                function setAccountState() {

                    for (var i = 0; i < 11; i++) {
                        if (!bridge.hasFlag(model.state, Math.pow(2, i)))
                            return stateNames[i]
                    }
                }

                property string accountState: setAccountState()

                Connections {
                    target: model
                    function onStateChanged() {
                        stateLabel.setAccountState()
                    }
                }

                text: Qt.formatDateTime(modified, "dd.MM.yy") + " - " + accountState;
            }

            Component.onCompleted: {
                stateLabel.setAccountState()
            }
        }

        ColumnLayout {
            visible: !settingsDialog.invisible.checked
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight

            Label {
                property var address: habitat["address"]
                text: address.street + ' ' + address.city + ' ' + address.zip + ' ' + address.canton
                font.bold: true
                visible: (Object.keys(address).length)
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                wrapMode: Text.Wrap
            }

            Label {
                text: advisorFirstName + ' ' + advisorLastName + ' ' + company
                font.italic: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                wrapMode: Text.Wrap
            }
        }

        ListView {
            interactive: false
            implicitHeight: contentHeight
            implicitWidth: accountRow.width / 3
            Layout.alignment: Qt.AlignRight
            model: owners
            delegate: Label {
                required property var modelData
                required property int index
                text: modelData.firstName + ' ' + modelData.lastName
            }
            visible: !settingsDialog.invisible.checked
        }
    }

    onClicked: {
        bridge.accountId = model.id
        bridge.accountState = model.state
        accountsPages.loadItem()
    }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: Material.background
        opacity: .8
    }
}
