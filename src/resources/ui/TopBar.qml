import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

import Interface

RowLayout {
    visible: false
    spacing: 0

    property alias searchBar: search

    ComboBox {
        id: sort
        Layout.rightMargin: -12

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

        onActivated: {
            rootStack.currentIndex === 0 ?
                         accountModel.sortRole = currentIndex
                       : userModel.sortRole = currentIndex
        }

        model: rootStack.currentIndex < 1 ?
                   [qsTr("Création"),
                    qsTr("Dernière modification"),
                    qsTr("Acronyme"),
                    qsTr("Partenaire"),
                    qsTr("NPA"),
                    qsTr("Canton"),
                    qsTr("Conseiller"),
                    qsTr("Société")]
                 : [qsTr("Nom"),
                    qsTr("Sosciete")]

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
                 || rootStack.currentIndex === 2
        icon.source: "qrc:/icons/arrow-left.svg"
        font.bold: true
        onClicked: if (rootStack.currentIndex === 0) {
                       accountsPages.validateItem()
                       accountsPages.currentIndex = 0
                   } else if (rootStack.currentIndex === 1) {
                       users.validate(currentUser.id)
                       usersPages.currentIndex = 0
                   } else { rootStack.currentIndex = 0 }
        background: Rectangle {
            implicitHeight: Material.buttonHeight
            radius: 2
            color: Material.backgroundColor
        }
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
                    id: infantButton
                    text: qsTr("Enfants")
                    highlighted: accountsPages.currentIndex == 2 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    enabled: false
                    onClicked: {
                        accountsPages.validateItem()
                        busyDialog.open()
                        infants.loadFrom(bridge.accountId)
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
                }
            }
        }

        function enableButtons() {

            if (bridge.accountHasFlag(1))
                infantButton.enabled = true
            else
                infantButton.enabled = false

            if (bridge.accountHasFlag(2))
                habitatButton.enabled = true
            else
                habitatButton.enabled = false

            if (bridge.accountHasFlag(4))
                exteriorButton.enabled = true
            else
                exteriorButton.enabled = false

            if (bridge.accountHasFlag(8))
                documentButton.enabled = true
            else
                documentButton.enabled = false

            if (bridge.accountHasFlag(16))
                stateButton.enabled = true
            else
                stateButton.enabled = false
        }

        Connections {
            target: accounts
            function onDataChangedAt(index : int) {
                buttonView.enableButtons()
            }
        }

        Connections {
            target: bridge
            function onAccountIdChanged() {
                buttonView.enableButtons()
            }
        }
    }

    Item {
        Layout.fillWidth: true
        visible: rootStack.currentIndex > 0
    }

    Image {
        id: settings
        Layout.margins: 2
        Layout.fillHeight: true
        source: "qrc:/images/ViageLogo.svg"
        sourceSize.height: searchBar.height

        MouseArea {
            anchors.fill: parent
            onClicked: settingsDialog.open()
        }
    }
}
