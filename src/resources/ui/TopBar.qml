import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

RowLayout {
    visible: false
    spacing: 0

    property alias searchBar: search

    ComboBox {
        id: sort
        Layout.rightMargin: -12

        visible: accountsPages.currentIndex < 1 && advisorsPages.currentIndex < 1
        contentItem: IconLabel {
            leftPadding: 6
            rightPadding: -18
            icon.width: 20
            icon.height: 20
            icon.source: "qrc:/icons/filter.svg"
            icon.color: Material.foreground
        }

        onActivated: rootStack.currentIndex < 1 ?
                         accountModel.setSortIndex = currentIndex
                       : advisorModel.setSortIndex = currentIndex

        model: rootStack.currentIndex < 1 ?
                   [qsTr("Creation"),
                    qsTr("Dernière modification"),
                    qsTr("Acronyme"),
                    qsTr("Partenaire"),
                    qsTr("Code Postal"),
                    qsTr("Canton"),
                    qsTr("Conseiller"),
                    qsTr("Sosciete")]
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
        visible: accountsPages.currentIndex < 1 && advisorsPages.currentIndex < 1
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
        visible: accountsPages.currentIndex < 1 && advisorsPages.currentIndex < 1
        onVisibleChanged: if (!visible) { focus = false }
        onTextChanged: rootStack.currentIndex === 0 ?
                           accountModel.setFilterFixedString(text.toString())
                         : advisorModel.setFilterFixedString(text.toString())
    }

    Button {
        id: backButton
        visible: accountsPages.currentIndex > 0 || advisorsPages.currentIndex > 0
        icon.source: "qrc:/icons/arrow-left.svg"
        font.bold: true
        onClicked: if (rootStack.currentIndex === 0) {
                       accountsPages.validateItem()
                       accountsPages.currentIndex = 0
                   } else {
                       advisorsPages.currentIndex = 0
                   }
        background: Rectangle {
            implicitHeight: Material.buttonHeight
            radius: 2
            color: Material.backgroundColor
        }
    }

    ScrollView {
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
                    id: infoButton
                    text: qsTr("Partenaires")
                    highlighted: accountsPages.currentIndex == 1 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if (currentAccount.state >= 0) {
                                   accountsPages.validateItem()
                                   owners.loadFrom(currentAccount.index)
                               }
                }

                RoundButton {
                    id: infantButton
                    text: qsTr("Enfants")
                    highlighted: accountsPages.currentIndex == 2 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if (currentAccount.state >= 1) {
                                   accountsPages.validateItem()
                                   infants.loadFrom(currentAccount.index)
                               }
                    visible: currentAccount.state >= 1
                }

                RoundButton {
                    id: habitatButton
                    text: qsTr("Habitat")
                    highlighted: accountsPages.currentIndex == 3 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if (currentAccount.state >= 2) {
                                   accountsPages.validateItem()
                                   habitat.loadFrom(currentAccount.index)
                               }
                    visible: currentAccount.state >= 2
                }

                RoundButton {
                    id: exteriorButton
                    text: qsTr("Exterieur")
                    highlighted: accountsPages.currentIndex == 4 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if (currentAccount.state >= 4) {
                                   accountsPages.validateItem()
                                   exterior.loadFrom(currentAccount.index)
                               }
                    visible: currentAccount.state >= 4
                }

                RoundButton {
                    id: documentButton
                    text: qsTr("Documents")
                    highlighted: accountsPages.currentIndex == 5 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: if (currentAccount.state >= 8) {
                                   accountsPages.validateItem()
                                   documents.loadFrom(currentAccount.index)
                               }
                    visible: currentAccount.state >= 8
                }

                RoundButton {
                    id: signatureButton
                    text: qsTr("Etats")
                    highlighted: accountsPages.currentIndex == 6 ? true : false
                    font.capitalization: Font.MixedCase
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    visible: currentAccount.state >= 16
                }
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

    /*{
        id: settings
        icon.source: "qrc:/icons/ellipsis-v.svg"
        icon.width: height / 5.5
        onClicked: settingsDialog.open()
        Layout.alignment: Qt.AlignRight

        background: Rectangle {
            implicitHeight: Material.buttonHeight
            implicitWidth: Material.buttonHeight
            radius: 2
            color: Material.backgroundColor
        }
    }*/

    //    Button {
    //        id: settings
    //        icon.source: "qrc:/icons/ellipsis-v.svg"
    //        icon.width: height / 5.5
    //        onClicked: settingsDialog.open()
    //        Layout.alignment: Qt.AlignRight

    //        background: Rectangle {
    //            implicitHeight: Material.buttonHeight
    //            implicitWidth: Material.buttonHeight
    //            radius: 2
    //            color: Material.backgroundColor
    //        }
    //    }
}
