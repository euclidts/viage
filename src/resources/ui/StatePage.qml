import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: false

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                Layout.minimumWidth: 200

                ColumnLayout {
                    Layout.minimumWidth: 200
                    Layout.margins: 12

                    Label {
                        Layout.leftMargin: -6
                        text: qsTr("Demande de Dossier")
                        font.bold: true
                    }

                    Label {
                        text: qsTr("Envoyer le code de validation au ")
                        font.italic: true
                    }

                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "phone"
                        model: OwnersModel { list: owners }
                    }

                    TextField {
                        id: code
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("Veuillez saisir le code reçu par sms")
                        Layout.fillWidth: true
                    }

                    Button {
                        id: validateButton
                        highlighted: true
                        text: qsTr("Siger électroniquement")
                        Layout.alignment: Qt.AlignRight
                        visible: code.text !== ""
                        onClicked:
                            //                    if (!foucsOnEmpty())
                        {
                            completed = true
                            if (currentAccount.state < accountsPages.currentIndex)
                                currentAccount.state = accountsPages.getComplitionIndex()
                        }
                    }
                }

                //    onCompleted: {
                //        if (currentAccount.state > 0) {
                //            editing = false
                //            completed = true
                //        }

                //        contentItem.contentY = this.y
                //    }
            }
        }
    }
}
