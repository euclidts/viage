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

                        IntChooser {
                            name: qsTr("Nombre de Pièces")
                            minimum: 1
                            maximum: 50
                            numberOf: habitat.rooms
                            onEdit: function(val) { habitat.rooms = val }
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
                                name: qsTr("brut (m2)")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.rawSurface
                                onEdit: function(val) { habitat.rawSurface = val }
                            }

                            IntChooser {
                                name: qsTr("net (m2)")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.surface
                                onEdit: function(val) { habitat.surface = val }
                            }

                            IntChooser {
                                name: qsTr("M2 Construits")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.m2Constructed
                                onEdit: function(val) { habitat.m2Constructed = val }
                            }

                            IntChooser {
                                name: qsTr("M2 Disponibles")
                                minimum: 1
                                maximum: 1000
                                numberOf: habitat.m2Available
                                onEdit: function(val) { habitat.m2Available = val }
                            }
                        }
                    }
                }

                IntChooser {
                    name: qsTr("Nombre de M3")
                    minimum: 0
                    maximum: 100000
                    numberOf: habitat.m3s
                    onEdit: function(val) { habitat.m3s = val }
                }
            }
        }
    }
}
