import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

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

                DateChooserLocal {
                    id: transactionDateChooser
                    Layout.margins: 6
                    maxYear: 30
                    name: qsTr("Date estimée de la transaction")
                }


                ListModel {
                    id: seniorCitizens
                }

                Component.onCompleted: {
                    seniorCitizens.append({ sex: 0, birthDay: "1950/01/01" })
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

                    model: seniorCitizens

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
                            birthDay: new Date(model.birthDay)
                            //birthDay: model.birthDay //|| new Date(1990, 0, 1)
                            onDateChanged: seniorCitizens.setProperty(index, "birthDay",
                                                             Qt.formatDate(birthDay, "yyyy/MM/dd"))
                        }
                    }
                }

                RoundButton {
                    property bool single: seniorCitizens.count === 1
                    text: single ? qsTr("Ajouter un partenaire") : qsTr("Supprimer un partenaire")
                    icon.source: single ? "qrc:/icons/plus.svg" : "qrc:/icons/trash-alt.svg"
                    highlighted: single

                    onClicked: {
                        if (single) {
                            seniorCitizens.append({ sex: 1, birthDay: "1950/01/01"})
                        } else {
                            seniorCitizens.remove(seniorCitizens.count - 1)
                        }
                    }
                }

                GridLayout {
                    Layout.leftMargin: 6
                    Layout.bottomMargin: 6
                    rowSpacing: 6
                    columns: 2

                    IntChooser {
                        id: valueChooser
                        name: qsTr("Valeur estimée du bien")
                        numberOf:1500000
                        minimum: 50000
                        maximum: 15000000
                        step: 1000
                        onEdit: value => numberOf = value
                    }

                    RoundButton {
                        text: qsTr("Calculer")
                        icon.source: "qrc:/icons/calculator.svg"
                        onClicked: {
                            if (seniorCitizens.count < 1 || seniorCitizens.count > 2) {
                                console.error("Il faut 1 ou 2 partenaires.")
                                return
                            }

                            function sexToChar(sex) { return sex === 0 ? "M" : "F"; }

                            var payload = {
                                DateTransaction: Qt.formatDate(transactionDateChooser.birthDay, "yyyy/MM/dd"),
                                ValeurBien: valueChooser.numberOf
                            }

                            if (seniorCitizens.count >= 1) {
                                var p1 = seniorCitizens.get(0)
                                payload.Person1 = {
                                    Sex: sexToChar(p1.sex),
                                    Birthdate: p1.birthDay
                                }
                            }

                            if (seniorCitizens.count >= 2) {
                                var p2 = seniorCitizens.get(1)
                                payload.Person2 = {
                                    Sex: sexToChar(p2.sex),
                                    Birthdate: Qt.formatDate(p2.birthDay, "yyyy/MM/dd")
                                }
                            }

                            console.error(JSON.stringify(payload))
                            var xhr = new XMLHttpRequest()
                            xhr.open("POST", "http://127.0.0.1:8000/Account/Usufruit/Calcul?format=json")
                            xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8")
                            xhr.setRequestHeader("Accept", "application/json")

                            xhr.onreadystatechange = function() {
                                if (xhr.readyState === XMLHttpRequest.DONE) {
                                    if (xhr.status >= 200 && xhr.status < 300) {
                                        var result = JSON.parse(xhr.responseText)
                                        usufruit.text = Math.round(result.usufruit).toLocaleString(Qt.locale())
                                        bouquet.text = Math.round(result.bouquet).toLocaleString(Qt.locale())
                                    } else {
                                        console.error("Erreur API :", xhr.status, xhr.responseText)
                                    }
                                }
                            }

                            xhr.send(JSON.stringify(payload))
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
                        text: 0 === 0 ? "" : rent.dab.toLocaleString(Qt.locale())
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        text: qsTr("Bouquet :")
                        font.bold: true
                        Layout.alignment: Qt.AlignRight
                    }

                    Label {
                        id:bouquet
                        text: 0 === 0 ? "" : rent.bou.toLocaleString(Qt.locale())
                        Layout.alignment: Qt.AlignRight
                    }

                }
            }
        }
    }
}
