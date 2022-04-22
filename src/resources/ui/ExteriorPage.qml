import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Places

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool editing: true
    property bool completed: false

    onVisibleChanged: if (visible) checkCompeted()

    function checkCompeted() {
        if (exterior.rating === 0) {
            exteriorPage.completed = false
            return
        }
        exteriorPage.completed = true
    }

    Connections {
        target: exterior
        function onRatingChanged() {
            exteriorPage.checkCompeted()
        }
    }

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                Layout.minimumWidth: 200

                ColumnLayout {
                    spacing: 12
                    Layout.margins: 12
                    Layout.fillWidth: true

                    GroupBox {
                        label: Label {
                            text: qsTr("Parking")
                            font.italic: true
                        }
                        Layout.topMargin: 12
                        Layout.fillWidth: true
                        contentHeight: contentItem.childrenRect.height

                        ColumnLayout {
                            width: parent.width
                            spacing: 0

                            RowLayout {
                                spacing: 0

                                CheckBox {
                                    checked: exterior.parking
                                    onCheckStateChanged: exterior.parking = checked
                                    text: qsTr("Disponible")
                                    checkable: editing
                                }

                                IntChooser {
                                    maximum: 20
                                    numberOf: exterior.parkingSurface
                                    onEdit: function(val) { exterior.parkingSurface = val }
                                    canEdit: editing
                                    name: qsTr("Surface (m2)")
                                    visible: exterior.parking
                                }

                                TextField {
                                    text: exterior.parkingSurface + ' m2'
                                    readOnly: true
                                    visible: !editing
                                    Layout.fillWidth: true
                                }

                                IntChooser {
                                    maximum: 10
                                    numberOf: exterior.parkingSpots
                                    onEdit: function(val) { exterior.parkingSpots = val }
                                    canEdit: editing
                                    name: qsTr("Nombre de places")
                                    visible: exterior.parking
                                }
                            }

                            TextField {
                                text: exterior.parkingSpots + ' places'
                                readOnly: true
                                visible: !editing
                                Layout.fillWidth: true
                            }

                            LabeledTextField {
                                name: qsTr("Type de places")
                                textOf: exterior.parkingType
                                canEdit: editing
                                onEdit: function(txt) { exterior.parkingType = txt }
                                placeHolder: qsTr("* Optionnel")
                                visible: exterior.parking
                            }
                        }
                    }

                    GroupBox {
                        label: Label {
                            text: qsTr("Terrain")
                            font.italic: true
                        }
                        Layout.topMargin: 12
                        Layout.fillWidth: true
                        contentHeight: contentItem.childrenRect.height

                        ColumnLayout {
                            width: parent.width
                            spacing: 0

                            LabeledTextField {
                                name: qsTr("Description")
                                textOf: exterior.terrainDescription
                                canEdit: editing
                                onEdit: function(txt) { exterior.terrainDescription = txt }
                                placeHolder: qsTr("* Optionnel")
                            }

                            IntChooser {
                                name: qsTr("Surface (m2)")
                                minimum: 1
                                maximum: 2000
                                numberOf: exterior.terrainSurface
                                onEdit: function(val) { exterior.terrainSurface = val }
                                canEdit: editing
                            }

                            TextField {
                                text: "Surface de " + exterior.terrainSurface + ' m2'
                                readOnly: true
                                visible: !editing
                                placeholderText: qsTr("* Optionnel")
                            }
                        }
                    }

                    RowLayout {
                        Label {
                            text: qsTr("Etat général")
                            font.bold: true
                        }

                        ToolButton {
                            icon.source: exterior.rating < 1 ? "qrc:/icons/empty-star.svg"
                                                             : "qrc:/icons/star.svg"
                            icon.color: exterior.rating < 1 ? Material.foreground
                                                            : Material.accent
                            onClicked: exterior.rating = 1
                        }

                        ToolButton {
                            icon.source: exterior.rating < 2 ? "qrc:/icons/empty-star.svg"
                                                             : "qrc:/icons/star.svg"
                            icon.color: exterior.rating < 2 ? Material.foreground
                                                            : Material.accent
                            onClicked: exterior.rating = 2
                        }

                        ToolButton {
                            icon.source: exterior.rating < 3 ? "qrc:/icons/empty-star.svg"
                                                             : "qrc:/icons/star.svg"
                            icon.color: exterior.rating < 3 ? Material.foreground
                                                            : Material.accent
                            onClicked: exterior.rating = 3
                        }

                        ToolButton {
                            icon.source: exterior.rating < 4 ? "qrc:/icons/empty-star.svg"
                                                             : "qrc:/icons/star.svg"
                            icon.color: exterior.rating < 4 ? Material.foreground
                                                            : Material.accent
                            onClicked: exterior.rating = 4
                        }

                        ToolButton {
                            icon.source: exterior.rating < 5 ? "qrc:/icons/empty-star.svg"
                                                             : "qrc:/icons/star.svg"
                            icon.color: exterior.rating < 5 ? Material.foreground
                                                            : Material.accent
                            onClicked: exterior.rating = 5
                        }
                    }

                    //            Button {
                    //                text: qsTr("Modifier")
                    //                highlighted: true
                    //                Layout.alignment: Qt.AlignRight
                    //                visible: !editing
                    //                onClicked: editing = true
                    //            }

                    //            Button {
                    //                id: validateButton
                    //                highlighted: true
                    //                text: qsTr("Valider")
                    //                Layout.alignment: Qt.AlignRight
                    //                visible: editing
                    //                onClicked:
                    //                    //                if (!foucsOnEmpty())
                    //                {
                    //                    editing = false
                    //                    completed = true
                    //                    exterior.validate(currentAccount.index)
                    //                    if (exterior.state < accountsPages.currentIndex)
                    //                        exterior.state = accountsPages.getComplitionIndex()
                    //                }
                    //            }
                }
            }
        }

        //    onCompleted: {
        //        if (currentAccount.state > 3) {
        //            editing = false
        //            completed = true
        //        }

        //        contentItem.contentY = this.y
        //    }
    }
}
