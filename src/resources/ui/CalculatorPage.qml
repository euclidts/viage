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

                DateChooser {
                    Layout.margins: 6
                    dateOf: rent
                    maxYear: 30
                    name: qsTr("Date de l'évaluation")
                }

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
                        spacing: 0
                        width: parent.width

                        required property var model
                        required property int index

                        Label {
                            Layout.margins: 6
                            text: qsTr("Patenaire " + (index + 1))
                            font.bold: true
                        }

                        SexChooser {
                            sexOf: model
                        }

                        DateChooser {
                            dateOf: model
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
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: rent.estimation === 0 ? "" : rent.estimation.toLocaleString(Qt.locale())
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: qsTr("Droit d'habitation :")
                        font.bold: true
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: rent.dab === 0 ? "" : rent.dab.toLocaleString(Qt.locale())
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: qsTr("Bouquet :")
                        font.bold: true
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: rent.bou === 0 ? "" : rent.bou.toLocaleString(Qt.locale())
                        Layout.alignment: Qt.AlignRight
                    }

//                    Label {
//                        text: qsTr("Estimation d'une rente :")
//                        font.bold: true
//                        Layout.alignment: Qt.AlignRight
//                    }

//                    Label {
//                        text: rent.rva === 0 ? "" : rent.rva.toLocaleString(Qt.locale())
//                        Layout.alignment: Qt.AlignRight
//                    }
                }
            }
        }
    }
}
