import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                spacing: 12
                Layout.margins: 12
                Layout.minimumWidth: 200
                width: parent.width

                ListView {
                    id: seniorList
                    interactive: false
                    implicitHeight: childrenRect.height
                    Layout.fillWidth: true
                    leftMargin: 6
                    rightMargin: 6
                    topMargin: 3
                    bottomMargin: 3
                    spacing: 6

                    model : SeniorCitizenModel { list: seniorCitizens }

                    delegate: ColumnLayout {
                        id: senior
                        spacing: 0
                        width: parent.width

                        required property var model
                        required property int index

                        GroupBox {
                            label: Label {
                                text: qsTr("Patenaire " + (index + 1))
                                font.bold: true
                            }
                            Layout.topMargin: 12
                            Layout.fillWidth: true

                            ColumnLayout {
                                width: parent.width

                                ButtonGroup {
                                    id: sexGroup
                                    buttons: sexRow.children
                                    onCheckedButtonChanged: model.sex = checkedButton.index
                                }

                                RowLayout {
                                    id: sexRow
                                    spacing: 0
                                    Layout.margins: 0

                                    RadioButton {
                                        text: qsTr("Monsieur")
                                        readonly property int index: 0
                                        checked: model.sex === index
                                    }

                                    RadioButton {
                                        text: qsTr("Madame")
                                        readonly property int index: 1
                                        checked: model.sex === index
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    Layout.fillWidth: true

                                    RowLayout {
                                        spacing: 0

                                        IntChooser {
                                            name: qsTr("Jour")
                                            minimum: 1
                                            maximum: 31
                                            numberOf: model.birthDay.getDate()
                                            onEdit: function(val) {
                                                let date = model.birthDay
                                                date.setDate(val)
                                                model.birthDay = date
                                            }
                                        }

                                        ColumnLayout {
                                            spacing: 0

                                            Label {
                                                text: qsTr("Mois")
                                                font.italic: true
                                            }

                                            ComboBox {
                                                Layout.minimumWidth: 164
                                                model: [qsTr("Janvier"),
                                                    qsTr("Fevrier"),
                                                    qsTr("Mars"),
                                                    qsTr("Avril"),
                                                    qsTr("Mai"),
                                                    qsTr("Juin"),
                                                    qsTr("Juillet"),
                                                    qsTr("Août"),
                                                    qsTr("Septembre"),
                                                    qsTr("Octobre"),
                                                    qsTr("Novembre"),
                                                    qsTr("Decembre")]
                                                onActivated:
                                                {
                                                    let date = senior.model.birthDay
                                                    date.setMonth(currentIndex)
                                                    senior.model.birthDay = date
                                                }
                                                currentIndex: senior.model.birthDay.getMonth()
                                            }
                                        }
                                    }

                                    IntChooser {
                                        readonly property int currentYear: new Date().getFullYear()

                                        minimum: currentYear - 120
                                        maximum: currentYear - 65
                                        name: qsTr("Année")
                                        numberOf: model.birthDay.getFullYear()
                                        onEdit: function(val) {
                                            let date = model.birthDay
                                            date.setFullYear(val)
                                            senior.model.birthDay = date
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                RoundButton {
                    readonly property bool single: seniorList.count === 1
                    text: (single ? qsTr("Ajouter") : qsTr("Suprimer")) + " un partenaire"
                    icon.source: single ? "qrc:/icons/plus.svg"
                                        : "qrc:/icons/trash-alt.svg"
                    onClicked: single ? seniorCitizens.appendItems(1)
                                      : seniorCitizens.removeItems(1)
                    highlighted: single
                }

                GridLayout {
                    Layout.leftMargin: 6
                    Layout.bottomMargin: 6
                    rowSpacing: 6
                    columns: 2

                    ColumnLayout {
                        spacing: 0

                        Label {
                            text: qsTr("Valeur de marché du bien")
                            font.italic: true
                            Layout.alignment: Qt.AlignHCenter
                        }

                        SpinBox {
                            from: 50000
                            to: 10000000
                            stepSize: 1000
                            editable: true
                            value: rent.marketPrice
                            locale: Qt.locale()
                            onValueModified: rent.marketPrice = value
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }
                    }

//                    ColumnLayout {
//                        spacing: 0

//                        Label {
//                            text: qsTr("Rente mensuelle")
//                            font.italic: true
//                            Layout.alignment: Qt.AlignHCenter
//                        }

//                        SpinBox {
//                            from: 0
//                            to: 10000
//                            stepSize: 1000
//                            editable: true
//                            value: rent.monthly
//                            locale: Qt.locale()
//                            onValueModified: rent.monthly = value
//                            inputMethodHints: Qt.ImhFormattedNumbersOnly
//                        }
//                    }

                    RoundButton {
                        text: qsTr("Calculer")
                        icon.source: "qrc:/icons/calculator.svg"
                        onClicked: rent.calculate()
                        highlighted: true
                    }

//                    RoundButton {
//                        text: qsTr("C")
//                        onClicked: rent.clear()
//                    }

                    Label {
                        text: qsTr("Valeur estimée du bien :")
                        font.bold: true
                    }

                    Label {
                        text: rent.estimation === 0 ? "" : rent.estimation.toLocaleString(Qt.locale())
                    }

                    Label {
                        text: qsTr("Droit d'habitation :")
                        font.bold: true
                    }

                    Label {
                        text: rent.dab === 0 ? "" : rent.dab.toLocaleString(Qt.locale())
                    }

                    Label {
                        text: qsTr("Bouquet :")
                        font.bold: true
                    }

                    Label {
                        text: rent.bou === 0 ? "" : rent.bou.toLocaleString(Qt.locale())
                    }

//                    Label {
//                        text: qsTr("Estimation de la valeur d'une rente :")
//                        font.bold: true
//                    }

//                    Label {
//                        text: rent.rva === 0 ? "" : rent.rva.toLocaleString(Qt.locale())
//                    }
                }
            }
        }
    }
}
