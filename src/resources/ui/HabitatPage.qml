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
        if (habitat.street === "") {
            habitatPage.completed = false
            return
        } else if (habitat.city === "") {
            habitatPage.completed = false
            return
        }
        habitatPage.completed = true
    }

    Connections {
        target: habitat
        function onStreetChanged() {
            habitatPage.checkCompeted()
        }
    }
    Connections {
        target: habitat
        function onCityChanged() {
            habitatPage.checkCompeted()
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
                        onCheckedButtonChanged: habitat.type = checkedButton.text
                    }

                    RowLayout {
                        ColumnLayout {
                            spacing: 0
                            visible: editing
                            Layout.rightMargin: 12

                            RadioButton {
                                text: qsTr("Maison individuelle")
                                ButtonGroup.group: habitatTypes
                                checked: habitat.type === text
                            }
                            RadioButton {
                                text: qsTr("Maison mitoyenne")
                                ButtonGroup.group: habitatTypes
                                checked: habitat.type === text
                            }

                            RadioButton {
                                text: qsTr("Appartement")
                                ButtonGroup.group: habitatTypes
                                checked: habitat.type === text
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
                                    name: qsTr("M2 Construit")
                                    minimum: 1
                                    maximum: 1000
                                    numberOf: habitat.m2Constructed
                                    onEdit: function(val) { habitat.m2Constructed = val }
                                }

                                IntChooser {
                                    name: qsTr("M2 Disponible")
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
                        name: qsTr("Equipement de proximité")
                        textOf: habitat.equipements
                        canEdit: editing
                        onEdit: function(txt) {
                            habitat.equipements = txt
                            habitatPage.checkCompeted()
                        }
                    }
                }
            }
        }
    }
}
