import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtCore

import People

ListView {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    spacing: 6
    clip: true

    model : OwnersModel { list: owners }

    property bool completed: false

    onCountChanged: busyDialog.close()

    delegate: BackgroundRect {
        id: owner

        required property var model
        required property int index
        property bool editing: true

        function checkCompleted() {

            if (ownersPage.completed) return

            if (model.firstName === "") {
                ownersPage.completed = false
                return
            } else if (model.lastName === "") {
                ownersPage.completed = false
                return
            } else if (model.phone === "") {
                ownersPage.completed = false
                return
            } else if (model.street === "") {
                ownersPage.completed = false
                return
            } else if (model.city === "") {
                ownersPage.completed = false
                return
            } else if (model.avs === "") {
                ownersPage.completed = false
                return
            } else if (model.civilStatus === 0) {
                ownersPage.completed = false
                return
            }
            ownersPage.completed = true
        }

        Connections {
            target: ownersPage.model
            function onDataChanged(topLeft, bottomRight, roles) {
                if (topLeft.row === model.index) {
                    owner.checkCompleted()
                }
            }
        }

        Connections {
            target: ownersPage
            function onVisibleChanged() {
                if (ownersPage.visible) {
                    owner.checkCompleted()
                }
            }
        }

        InfantDelegate {
            title: qsTr("Partenaire")
            model: owner.model

            ColumnLayout {
                spacing: 0
                Layout.leftMargin: 12
                Layout.rightMargin: 12

                LabeledTextField {
                    name: qsTr("AVS")
                    textOf: model.avs
                    canEdit: owner.editing
                    onEdit: function(txt) { model.avs = txt }
                    inputHint: Qt.ImhFormattedNumbersOnly
                    validator: RegularExpressionValidator {
                        regularExpression: /\d{13}?$/
                    }
                }

                GroupBox {
                    label: Label {
                        text: qsTr("Date de naissance")
                        font.italic: true
                    }
                    Layout.topMargin: 12
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        ColumnLayout {
                            spacing: 0
                            Layout.fillWidth: true
                            visible: owner.editing

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
                                            let date = owner.model.birthDay
                                            date.setMonth(currentIndex)
                                            owner.model.birthDay = date
                                        }
                                        currentIndex: owner.model.birthDay.getMonth()
                                    }
                                }
                            }

                            IntChooser {
                                property int currentYear: new Date().getFullYear()

                                minimum: currentYear - 120
                                maximum: currentYear
                                name: qsTr("Année")
                                numberOf: model.birthDay.getFullYear()
                                onEdit: function(val) {
                                    let date = model.birthDay
                                    date.setFullYear(val)
                                    owner.model.birthDay = date
                                }
                            }
                        }

                        TextField {
                            text: Qt.formatDate(model.birthDay, "dd.MM.yy")
                            readOnly: true
                            visible: !owner.editing
                            Layout.fillWidth: true
                        }
                    }
                }

                AddressChooser {
                    addressOf: model
                    canEdit: owner.editing
                }

                GroupBox {
                    label: Label {
                        text: qsTr("État civil")
                        font.italic: true
                    }
                    Layout.topMargin: 12
                    Layout.bottomMargin: 12
                    Layout.fillWidth: true

                    ButtonGroup {
                        id: civilStates
                        buttons: civilStateColumn.children
                        onCheckedButtonChanged: model.civilStatus = checkedButton.index
                    }

                    ColumnLayout {
                        width: parent.width

                        ColumnLayout {
                            id: civilStateColumn
                            spacing: 0
                            visible: !civilStateDisplay.visible

                            RadioButton {
                                text: qsTr("Célibataire")
                                readonly property int index: 1
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Marié(e)")
                                readonly property int index: 2
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Partenariat enregistré")
                                readonly property int index: 3
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Séparé(e)")
                                readonly property int index: 4
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Divorcé(e)")
                                readonly property int index: 5
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Partenariat dissous")
                                readonly property int index: 6
                                checked: model.civilStatus === index
                            }
                            RadioButton {
                                text: qsTr("Veuf")
                                readonly property int index: 7
                                checked: model.civilStatus === index
                            }
                        }

                        TextField {
                            id: civilStateDisplay
                            text: civilStates.checkedButton.text
                            readOnly: true
                            visible: !owner.editing
                            Layout.fillWidth: true
                        }
                    }
                }

                RowLayout {
                    spacing: 0

                    Button {
                        id: deleteButton
                        icon.source: "qrc:/icons/trash-alt.svg"
                        visible: owner.editing && model.index > 0
                        onClicked: owners.removeItems(model.index, model.index)
                    }
                }
            }
        }
    }
}
