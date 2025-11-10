import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import "qrc:/ui" 1.0



ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    function parseDate(str) {
        var parts = str.split("/")
        return new Date(parts[0], parts[1]-1, parts[2])
    }
    Connections{
        target:bridge
        onCalculOk: function(result) {
            usufruit.text = Math.round(result.usufruit).toLocaleString(Qt.locale())
            bouquet.text = Math.round(result.bouquet).toLocaleString(Qt.locale())
            busyDialog.close()
        }
        onCalculErreur: function(status, response) {
            console.error("Erreur calcul:", status, response)
            exceptionDialog.title = "Calcul"
            exceptionDialog.text = response
            exceptionDialog.open()
            busyDialog.close()
        }
    }


    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                spacing: 12
                Layout.margins: 12
                Layout.minimumWidth: 200
                width: parent.width

                DateChooserLocal {
                    id: transactionDateChooser
                    dateValue: CalculDataModel.transactionDate
                    Layout.margins: 6
                    maxYear: 30
                    name: qsTr("Date estimée de la transaction")
                    onDateChanged: d => CalculDataModel.transactionDate = d
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

                    model: CalculDataModel.seniorCitizens

                    delegate: ColumnLayout {
                        spacing: 0
                        width: parent.width

                        Label {
                            Layout.margins: 6
                            text: qsTr("Partenaire ") + (index + 1)
                            font.bold: true
                        }

                        SexChooserLocal {
                            sex: model.sex
                            onSexChanged: model.sex = sex
                        }

                        DateChooserLocal {
                            Layout.margins: 6
                            name: qsTr("Date de naissance")
                            dateValue: parseDate(model.birthDay)
                            onDateChanged: CalculDataModel.seniorCitizens.setProperty(index, "birthDay",
                                                             Qt.formatDate(dateValue, "yyyy/MM/dd"))
                        }
                    }
                }

                RoundButton {
                    property bool single: CalculDataModel.getSeniorCitizensSingle()
                    text: single ? qsTr("Ajouter un partenaire") : qsTr("Supprimer un partenaire")
                    icon.source: single ? "qrc:/icons/plus.svg" : "qrc:/icons/trash-alt.svg"
                    highlighted: single

                    onClicked: {
                        if (single) {
                            CalculDataModel.seniorCitizens.append({ sex: 1, birthDay: "1950/01/01"})
                        } else {
                            CalculDataModel.seniorCitizens.remove(CalculDataModel.seniorCitizens.count - 1)
                        }
                    }
                }
                Component.onCompleted: {
                    CalculDataModel.busyDialog = busyDialog
                }

                GridLayout {
                    Layout.leftMargin: 6
                    Layout.bottomMargin: 6
                    rowSpacing: 6
                    columns: 2

                    IntChooser {
                        id: valueChooser
                        name: qsTr("Valeur estimée du bien")
                        numberOf: CalculDataModel.valueBien
                        minimum: 50000
                        maximum: 15000000
                        step: 1000
                        onEdit: value => CalculDataModel.valueBien = value
                    }

                    RoundButton {
                        text: qsTr("Calculer")
                        icon.source: "qrc:/icons/calculator.svg"
                        onClicked: {
                            busyDialog.open()
                            var pl = CalculDataModel.getPayload()
                            bridge.calculerUsufruit(pl);
                        }
                        highlighted: true
                    }

                    Label {
                        text: qsTr("Usufruit :")
                        font.bold: true
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        id: usufruit
                        text: ""
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: qsTr("Bouquet :")
                        font.bold: true
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        id:bouquet
                        text: ""
                        Layout.alignment: Qt.AlignRight
                    }

                }
            }
        }
    }
}
