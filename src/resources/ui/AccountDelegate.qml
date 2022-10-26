import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import Data
import Places
import Interface

ItemDelegate {
    width: window.width
    leftInset: 6
    rightInset: 6
    topInset: 3
    bottomInset: 3

    contentItem: RowLayout {

        GridLayout {
            columns: 2
            Layout.preferredWidth: parent.width / 3

            Label {
                text: Qt.formatDateTime(created, "dd.MM.yy")
                wrapMode: Text.Wrap
            }

            Label {
                text: acronym
                font.bold: true
                Layout.fillWidth: true
                wrapMode: Text.Wrap
            }

            Label {
                text: Qt.formatDateTime(modified, "dd.MM.yy")
                wrapMode: Text.Wrap
            }

            Label {
                id: stateLabel

                property string accountState: setAccountState()

                function setAccountState() {
                    if (model.state === 31)
                        return qsTr("Complet")
                    else
                        for (var i = 0; i < 12; i++) {
                            if (!bridge.hasFlag(model.state, Math.pow(2, i)))
                                return stateNames[i]
                        }
                }

                Connections {
                    target: model
                    function onStateChanged() {
                        stateLabel.setAccountState()
                    }
                }

                text: accountState;
                wrapMode: Text.Wrap
            }

            Component.onCompleted: {
                stateLabel.setAccountState()
            }
        }

        ColumnLayout {
            visible: settingsDrawer.invisible.checked
            Layout.preferredWidth: parent.width / 3

            Label {
                property var address: habitat["address"]
                text: address.street === "" || address.city === ""
                      ? "" : address.street + ' ' + address.city + ' '
                      + address.zip + ' ' + address.canton
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
            }

            ListView {
                interactive: false
                implicitHeight: contentHeight
                Layout.fillWidth: true
                model: owners
                delegate: Label {
                    required property var modelData
                    required property int index
                    text: modelData.firstName + ' ' + modelData.lastName
                    horizontalAlignment: Text.AlignHCenter
                    font.italic: true
                    width: parent.width
                    wrapMode: Text.Wrap
                }
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width / 3

            ColumnLayout {
                visible: settingsDrawer.invisible.checked

                Label {
                    text: advisorFirstName + ' ' + advisorLastName
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.Wrap
                }

                Label {
                    text: model.company
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.Wrap
                }
            }

            RoundButton {
                visible: settingsDrawer.invisible.checked
                icon.source: "qrc:/icons/trash-alt.svg"
                ToolTip.visible: hovered
                ToolTip.text: "Suprimer le dossier"
                onClicked: onExceptionAction(ToolTip.text,
                                         "Le dossier selectioné serra suprimé définitivement",
                                         () => { accounts.remove(model.id) }, true)
            }
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
