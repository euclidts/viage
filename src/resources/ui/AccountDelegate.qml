import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import Places

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
                text: (acronym === "" ? id : acronym)
                      + " - " + Qt.formatDate(created, "dd.MM.yy")
            }

            Label {
                property string accountState: if (state < 16)
                                                  stateNames[0]
                                              else if (state === 32)
                                                  stateNames[1]
                                              else if (state === 64)
                                                  stateNames[2]
                                              else
                                                  stateNames[3]

                text: accountState + " - " + Qt.formatDate(modified, "dd.MM.yy");
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
                text: userFirstName + ' ' + userLastName + ' ' + company
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
        currentAccount = model
        accountsPages.loadItem()
    }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: Material.background
        opacity: .8
    }

    Component.onCompleted: {
        currentAccount = model
        if (onboarding) {
            onboarding = false
            accountsPages.loadItem()
        }
    }
}
