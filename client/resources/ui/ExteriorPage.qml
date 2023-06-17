import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Places

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: exterior.completed

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
                                    checked: exterior.hasParking
                                    onCheckStateChanged: exterior.hasParking = checked
                                    text: qsTr("Disponible")
                                }

                                IntChooser {
                                    maximum: 20
                                    numberOf: exterior.parkingSurface
                                    onEdit: function(val) { exterior.parkingSurface = val }
                                    name: qsTr("Surface (m²)")
                                    visible: exterior.hasParking
                                }

                                IntChooser {
                                    maximum: 10
                                    numberOf: exterior.parkingSpots
                                    onEdit: function(val) { exterior.parkingSpots = val }
                                    name: qsTr("Nombre de places")
                                    visible: exterior.hasParking
                                }
                            }

                            GroupBox {
                                label: Label {
                                    text: qsTr("Type de places")
                                    font.italic: true
                                }
                                visible: exterior.hasParking
                                Layout.topMargin: 12
                                Layout.bottomMargin: 12
                                Layout.fillWidth: true

                                GridLayout {
                                    id: parkingTypeColumn
                                    columns: portrait ? 2 : 3
                                    rows: 2
                                    flow: portrait ? GridLayout.LeftToRight
                                                   : GridLayout.TopToBottom

                                    CheckBox {
                                        id: bikeCheck
                                        text: qsTr("Moto")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }
                                    CheckBox {
                                        id: carCheck
                                        text: qsTr("Voiture")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }
                                    CheckBox {
                                        id: indoorCheck
                                        text: qsTr("Intérieur")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }
                                    CheckBox {
                                        id: outdoorCheck
                                        text: qsTr("Extérieur")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }
                                    CheckBox {
                                        id: individualCheck
                                        text: qsTr("Individuel")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }
                                    CheckBox {
                                        id: colectiveCheck
                                        text: qsTr("Collectif")
                                        onCheckStateChanged: parkingTypeColumn.setTypes()
                                    }

                                    property bool checking: false

                                    function setTypes() {
                                        if (!checking) {
                                            let bytes = 0
                                            if (bikeCheck.checked) bytes += 1
                                            if (carCheck.checked) bytes += 2
                                            if (indoorCheck.checked) bytes += 4
                                            if (outdoorCheck.checked) bytes += 8
                                            if (individualCheck.checked) bytes += 16
                                            if (colectiveCheck.checked) bytes += 32

                                            exterior.parkingType = bytes
                                        }
                                    }

                                    function checkTypes() {
                                        checking = true
                                        bikeCheck.checked = bridge.hasFlag(exterior.parkingType, 1)
                                        carCheck.checked = bridge.hasFlag(exterior.parkingType, 2)
                                        indoorCheck.checked = bridge.hasFlag(exterior.parkingType, 4)
                                        outdoorCheck.checked = bridge.hasFlag(exterior.parkingType, 8)
                                        individualCheck.checked = bridge.hasFlag(exterior.parkingType, 16)
                                        colectiveCheck.checked = bridge.hasFlag(exterior.parkingType, 32)
                                        checking = false
                                    }

                                    Connections {
                                        target: exterior
                                        function onParkingTypeChanged() {
                                            parkingTypeColumn.checkTypes()
                                        }
                                    }
                                }
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

                        GridLayout {
                            columns: portrait ? 1 : 2
                            width: parent.width

                            IntChooser {
                                name: qsTr("Surface (m²)")
                                minimum: 1
                                maximum: 20000
                                numberOf: exterior.terrainSurface
                                onEdit: function(val) { exterior.terrainSurface = val }
                            }

                            LabeledTextField {
                                name: qsTr("Description")
                                textOf: exterior.terrainDescription
                                onEdit: function(txt) { exterior.terrainDescription = txt }
                                placeHolder: qsTr("* Optionnel")
                            }
                        }
                    }

                    GroupBox {
                        label: Label {
                            text: qsTr("Equipements de proximité")
                            font.italic: true
                        }
                        Layout.topMargin: 12
                        Layout.bottomMargin: 12
                        Layout.fillWidth: true

                        GridLayout {
                            columns: portrait ? 2 : 3
                            id: equipementColumn

                            CheckBox {
                                id: healthCheck
                                text: qsTr("Santé")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }
                            CheckBox {
                                id: foodCheck
                                text: qsTr("Restauration")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }
                            CheckBox {
                                id: educationCheck
                                text: qsTr("Education")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }
                            CheckBox {
                                id: leasureCheck
                                text: qsTr("Loisirs")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }
                            CheckBox {
                                id: shopsCheck
                                text: qsTr("Commerces")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }
                            CheckBox {
                                id: transportsCheck
                                text: qsTr("Transports")
                                onCheckStateChanged: equipementColumn.setTypes()
                            }

                            property bool checking: false

                            function setTypes() {
                                if (!checking) {

                                    let bytes = 0
                                    if (healthCheck.checked) bytes += 1
                                    if (foodCheck.checked) bytes += 2
                                    if (educationCheck.checked) bytes += 4
                                    if (leasureCheck.checked) bytes += 8
                                    if (shopsCheck.checked) bytes += 16
                                    if (transportsCheck.checked) bytes += 32

                                    exterior.equipement = bytes
                                }
                            }

                            function checkTypes() {
                                checking = true
                                healthCheck.checked = bridge.hasFlag(exterior.equipement, 1)
                                foodCheck.checked = bridge.hasFlag(exterior.equipement, 2)
                                educationCheck.checked = bridge.hasFlag(exterior.equipement, 4)
                                leasureCheck.checked = bridge.hasFlag(exterior.equipement, 8)
                                shopsCheck.checked = bridge.hasFlag(exterior.equipement, 16)
                                transportsCheck.checked = bridge.hasFlag(exterior.equipement, 32)
                                checking = false
                            }

                            Connections {
                                target: exterior
                                function onEquipementChanged() {
                                    equipementColumn.checkTypes()
                                }
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
                }
            }
        }
    }
}
