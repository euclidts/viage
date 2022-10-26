import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

import Interface

RowLayout {
    spacing: 0
    height: visibleChildren.length !== 0 ? 48 : 0

    Behavior on height {
        NumberAnimation { duration: 200 }
    }

    property alias searchBar: search

    ComboBox {
        id: sort
        Layout.rightMargin: -12

        property var accountFilters: bridge.clearance === 4
                                     ? [qsTr("Dernière modification"),
                                        qsTr("Création"),
                                        qsTr("Acronyme"),
                                        qsTr("Partenaire"),
                                        qsTr("Conseiller"),
                                        qsTr("Société")]
                                     : [qsTr("Dernière modification"),
                                        qsTr("Création"),
                                        qsTr("Acronyme"),
                                        qsTr("Partenaire")]

        visible: accountsPages.currentIndex < 1 &&
                 usersPages.currentIndex < 1 &&
                 rootStack.currentIndex < 2
        contentItem: IconLabel {
            leftPadding: 6
            rightPadding: -18
            icon.width: 20
            icon.height: 20
            icon.source: "qrc:/icons/filter.svg"
            icon.color: Material.foreground
        }

        currentIndex: rootStack.currentIndex === 0 ?
                          accountModel.sortRole
                        : userModel.sortRole

        onActivated: {
            rootStack.currentIndex === 0 ?
                        accountModel.sortRole = currentIndex
                      : userModel.sortRole = currentIndex
        }

        model: rootStack.currentIndex < 1
               ? sort.accountFilters
               : [qsTr("Société"),
                  qsTr("Nom"),
                  qsTr("Role")]

        popup.width: 200

        background: Rectangle {
            radius: 2
            color: Material.backgroundColor

            PaddedRectangle {
                y: search.height - height - search.bottomPadding - 9
                width: parent.width - 12
                height: search.activeFocus || search.hovered ? 2 : 1
                color: search.activeFocus ? Material.accentColor
                                          : (search.hovered ? Material.primaryTextColor
                                                            : Material.hintTextColor)
                topPadding: -2
                clip: true
            }
        }
    }

    Button {
        id: magnifyingGlass
        visible: accountsPages.currentIndex < 1 &&
                 usersPages.currentIndex < 1 &&
                 rootStack.currentIndex < 2
        flat: true
        icon.source: search.text == "" ? "qrc:/icons/search.svg" : "qrc:/icons/times-circle.svg"
        background: Rectangle {
            radius: 2
            color: Material.backgroundColor

            PaddedRectangle {
                y: search.height - height - search.bottomPadding + 3
                width: parent.width
                height: search.activeFocus || search.hovered ? 2 : 1
                color: search.activeFocus ? Material.accentColor
                                          : (search.hovered ? Material.primaryTextColor
                                                            : Material.hintTextColor)
                topPadding: -2
                clip: true
            }
        }

        onClicked: search.clear()
    }

    TextField {
        id: search
        Layout.fillWidth: true
        placeholderText: qsTr("Recherche")
        visible: accountsPages.currentIndex < 1 &&
                 usersPages.currentIndex < 1 &&
                 rootStack.currentIndex < 2
        onVisibleChanged: if (!visible) { focus = false }
        onTextChanged: rootStack.currentIndex === 0 ?
                           accountModel.setFilterFixedString(text.toString())
                         : userModel.setFilterFixedString(text.toString())
    }

    Button {
        id: backButton
        visible: accountsPages.currentIndex > 0
                 || usersPages.currentIndex > 0
        icon.source: "qrc:/icons/arrow-left.svg"
        font.bold: true
        onClicked: if (rootStack.currentIndex === 0) {
                       accountsPages.validateItem()
                       accountsPages.currentIndex = 0
                   } else if (rootStack.currentIndex === 1) {
                       users.validate(selectedUser.filterRole)
                       usersPages.currentIndex = 0
                   }
        background: Rectangle {
            implicitHeight: Material.buttonHeight
            radius: 2
            color: Material.backgroundColor
        }
    }

    Label {
        text: rootStack.currentIndex === 2 ? qsTr("Calcul") : qsTr("Conseiller")
        font.bold: true
        visible: rootStack.currentIndex === 2
                 || (rootStack.currentIndex === 1
                     && usersPages.currentIndex === 1)
        Layout.leftMargin: 12
    }

    ScrollView {
        id: buttonView
        Layout.fillWidth: true
        visible: accountsPages.currentIndex > 0
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        Flickable {
            contentWidth: contentItem.childrenRect.width
            contentHeight: contentItem.childrenRect.height
            interactive: width < contentWidth
            clip: true

            RowLayout {
                RoundButton {
                    id: ownerButton
                    text: qsTr("Partenaires")
                    highlighted: accountsPages.currentIndex == 1 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        owners.loadFrom(bridge.accountId)
                    }
                }

                RoundButton {
                    id: contactButton
                    text: qsTr("Contacts")
                    highlighted: accountsPages.currentIndex == 2 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        contacts.loadFrom(bridge.accountId)
                    }
                }

                RoundButton {
                    id: habitatButton
                    text: qsTr("Habitat")
                    highlighted: accountsPages.currentIndex == 3 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        habitat.loadFrom(bridge.accountId)
                    }
                }

                RoundButton {
                    id: exteriorButton
                    text: qsTr("Exterieur")
                    highlighted: accountsPages.currentIndex == 4 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        exterior.loadFrom(bridge.accountId)
                    }
                }

                RoundButton {
                    id: documentButton
                    text: qsTr("Documents")
                    highlighted: accountsPages.currentIndex == 5 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        documents.loadFrom(bridge.accountId)
                    }
                }

                RoundButton {
                    id: stateButton
                    text: qsTr("Etats")
                    highlighted: accountsPages.currentIndex == 6 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: accountsPages.currentIndex = 6
                }

                Connections {
                    target: bridge
                    function onAccountStateChanged () {

                        if (bridge.accountHasFlag(16) && bridge.clearance < 4) {
                            ownerButton.visible = false
                            contactButton.visible = false
                            habitatButton.visible = false
                            exteriorButton.visible = false
                            documentButton.visible = false
                            documentButton.visible = false
                            stateButton.visible = true
                            stateButton.enabled = true
                        } else {
                            ownerButton.visible = true
                            contactButton.visible = true
                            contactButton.enabled = bridge.accountHasFlag(1)
                            habitatButton.visible = true
                            habitatButton.enabled = bridge.accountHasFlag(2)
                            exteriorButton.visible = true
                            exteriorButton.enabled = bridge.accountHasFlag(4)
                            documentButton.visible = true
                            documentButton.enabled = bridge.accountHasFlag(8)
                            if (bridge.clearance < 4) {
                                stateButton.visible = false
                            } else {
                                stateButton.visible = true
                                stateButton.enabled = bridge.accountHasFlag(16)
                            }
                        }
                    }
                }
            }
        }
    }

    Item {
        Layout.fillWidth: true
        visible: rootStack.currentIndex > 0 && rootStack.currentIndex < 3
    }

    Image {
        id: settings
        visible: rootStack.currentIndex < 3
        Layout.margins: 2
        Layout.fillHeight: true
        source: "qrc:/images/ViageLogo.svg"
        sourceSize.height: searchBar.height

        MouseArea {
            anchors.fill: parent
            onClicked: settingsDrawer.open()
            hoverEnabled: true
            ToolTip.visible: containsMouse
            ToolTip.text: "Options"
        }
    }
}
