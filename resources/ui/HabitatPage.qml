import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Places

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: habitat.completed

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                Layout.minimumWidth: 200

                ColumnLayout {
                    spacing: 12
                    Layout.margins: 12
                    Layout.fillWidth: true

                    Label {
                        Layout.leftMargin: -6
                        text: qsTr("Situation du bien")
                        font.bold: true
                    }

                    AddressChooser {
                        addressOf: habitat
                    }

                    ButtonGroup {
                        id: habitatTypes
                        buttons: habitatTypeColumn.children
                        onCheckedButtonChanged: habitat.habitatType = checkedButton.index
                    }

                    RowLayout {
                        ColumnLayout {
                            id: habitatTypeColumn
                            spacing: 0
                            Layout.rightMargin: 12

                            RadioButton {
                                text: qsTr("Maison individuelle")
                                readonly property int index: 1
                                checked: habitat.habitatType === index
                            }
                            RadioButton {
                                text: qsTr("Maison mitoyenne")
                                readonly property int index: 2
                                checked: habitat.habitatType === index
                            }

                            RadioButton {
                                text: qsTr("Appartement")
                                readonly property int index: 3
                                checked: habitat.habitatType === index
                            }
                        }

                        ColumnLayout {
                            spacing: 0
                            Layout.rightMargin: 12

                            MaterialButton {
                                fillWidth: false
                                text: qsTr("PPE")
                                icon.source: bridge.ppe ? "qrc:/icons/check-square.svg"
                                                        : "qrc:/icons/square.svg"
                                onClicked: {
                                    bridge.updatePPE()
                                    busyDialog.open()
                                }
                            }

                            IntChooser {
                                name: qsTr("Nombre de pièces")
                                minimum: 1
                                maximum: 50
                                numberOf: habitat.rooms
                                onEdit: (val) => { habitat.rooms = val }
                            }
                        }
                    }

                    GroupBox {
                        label: Label {
                            text: qsTr("Surface")
                            font.italic: true
                        }
                        Layout.topMargin: 12
                        Layout.fillWidth: true
                        contentHeight: contentItem.childrenRect.height

                        GridLayout {
                            columns: portrait ? 2 : 4

                            IntChooser {
                                name: qsTr("brut (m²)")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.rawSurface
                                onEdit: function(val) { habitat.rawSurface = val }
                            }

                            IntChooser {
                                name: qsTr("net (m²)")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.surface
                                onEdit: function(val) { habitat.surface = val }
                            }

                            IntChooser {
                                name: qsTr("m² construits")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.m2Constructed
                                onEdit: function(val) { habitat.m2Constructed = val }
                            }

                            IntChooser {
                                name: qsTr("m² disponibles")
                                minimum: 0
                                maximum: 1000
                                numberOf: habitat.m2Available
                                onEdit: function(val) { habitat.m2Available = val }
                            }
                        }
                    }

                    IntChooser {
                        name: qsTr("Nombre de m³")
                        minimum: 0
                        maximum: 100000
                        numberOf: habitat.m3s
                        onEdit: function(val) { habitat.m3s = val }
                    }
                }
            }
        }
    }
}
