import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import Places

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool editing: true
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
                        canEdit: editing
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
                            visible: editing
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
                            canEdit: editing
                        }
                    }

                    TextField {
                        text: habitat.rooms + ' Pièces'
                        readOnly: true
                        visible: !editing
                    }

                    GroupBox {
                        label: Label {
                            text: qsTr("Surface")
                            font.italic: true
                        }
                        Layout.topMargin: 12
                        Layout.fillWidth: true
                        contentHeight: contentItem.childrenRect.height

                        ColumnLayout {
                            spacing: 0

                            RowLayout {
                                Layout.fillWidth: true
                                visible: editing

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
                            }

                            TextField {
                                text: habitat.rawSurface + ' m2 ' + qsTr("brut")  + ' / ' + habitat.surface + ' m2 ' + qsTr("net")
                                readOnly: true
                                visible: !editing
                                Layout.fillWidth: true
                            }

                            RowLayout {
                                visible: !editing

                                Label {
                                    text: habitat.rawSurface
                                    Layout.alignment: Qt.AlignHCenter
                                }

                                Label {
                                    text: habitat.surface
                                    Layout.alignment: Qt.AlignHCenter
                                }
                            }

                            RowLayout {
                                Layout.fillWidth: true
                                visible: editing

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

                            TextField {
                                text: habitat.m2Construit + qsTr(" M2 Construit ")  + ' / ' + habitat.m2Available + qsTr(" M2 Disponible")
                                readOnly: true
                                visible: !editing
                                Layout.fillWidth: true
                            }
                        }
                    }

                    IntChooser {
                        name: qsTr("Nombre de M3")
                        minimum: 0
                        maximum: 100000
                        numberOf: habitat.m3s
                        onEdit: function(val) { habitat.m3s = val }
                        canEdit: editing
                    }

                    TextField {
                        text: habitat.m3s + ' m3'
                        readOnly: true
                        visible: !editing
                        Layout.fillWidth: true
                    }

                    LabeledTextField {
                        name: qsTr("Equipements de proximité")
                        placeHolder: qsTr("* Optionnel")
                        textOf: habitat.equipements
                        canEdit: editing
                        onEdit: function(txt) {
                            habitat.equipements = txt
                        }
                    }
                }
            }
        }
    }
}
