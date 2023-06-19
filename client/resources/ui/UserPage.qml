import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People
import Data

ListView {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    spacing: 6
    clip: true
    boundsBehavior: Flickable.StopAtBounds
    model : selectedUser

    property bool completed: false

    delegate: BackgroundRect {
        id: root

        required property var model
        required property int index

        UserFullDelegate {
            model: root.model
            index: root.index

            RowLayout {
                Layout.margins: 12

                GridLayout {
                    columns: 3

                    Label {
                        text: qsTr("Société")
                        font.italic: true
                    }

                    Label {
                        text: qsTr("Équipe")
                        font.italic: true
                    }

                    Label {
                        text: qsTr("Rôle")
                        font.italic: true
                    }

                    ComboBox {
                        id: companyCombo
                        editable: true
                        property string newText: ""
                        function setCompany(i : int) {
                            currentIndex = indexOfValue(i)
                            teams.loadFrom(currentValue)
                        }
                        function validateFunc() {
                            root.model.company = currentText
                            root.model.companyId = currentValue
                            busyDialog.open()
                            teams.loadFrom(currentValue)
                        }

                        textRole: "name"
                        valueRole: "id"
                        Layout.minimumWidth: 160
                        model: CompaniesModel { list: companies }
                        onAccepted: {
                            if (editText === "") {
                                root.model.company = ""
                                root.model.companyId = 0
                                return
                            }

                            var i = find(editText)

                            if (i === -1) {
                                newText = editText
                                onExceptionAction(qsTr("Ajouter une société"),
                                                  qsTr("Êtes-vous sûr de vouloir ajouter la nouvelle société ")
                                                  + editText
                                                  + " ?",
                                                  () => {
                                                      busyDialog.open()
                                                      var txt = '{ "name" : '
                                                      + '"'
                                                      + editText
                                                      + '"'
                                                      + ' }'
                                                      companies.addWith(JSON.parse(txt))
                                                  }, true)
                            } else {
                                currentIndex = i
                                validateFunc()
                            }
                        }
                        onActivated: validateFunc()
                        onCountChanged: {
                            var i = find(newText)

                            if (i !== -1) {
                                currentIndex = i
                                validateFunc()
                            }
                        }
                    }

                    ComboBox {
                        id: teamCombo
                        editable: true
                        property string newText: ""
                        function setTeam(i : int) {
                            currentIndex = indexOfValue(i)
                            validateFunc()
                        }
                        function validateFunc() {
                            root.model.team = currentText
                            root.model.teamId = currentValue
                        }

                        textRole: "caption"
                        valueRole: "id"
                        model: TeamsModel { list: teams }
                        Layout.minimumWidth: 160
                        onAccepted: {
                            if (editText === "" ) {
                                root.model.team = ""
                                root.model.teamId = 0
                                return
                            }

                            var i = find(editText)

                            if (i === -1) {
                                newText = editText
                                onExceptionAction(qsTr("Ajouter une équipe"),
                                                  qsTr("Êtes-vous sûr de vouloir ajouter l'équipe ")
                                                  + editText
                                                  + " ?",
                                                  () => {
                                                      busyDialog.open()
                                                      var txt = '{ "caption" : '
                                                      + '"'
                                                      + editText
                                                      + '"'
                                                      + ' }'
                                                      teams.addInWith(root.model.companyId, JSON.parse(txt))
                                                  }, true)
                            } else {
                                currentIndex = i
                                validateFunc()
                            }
                        }
                        onActivated: validateFunc()
                        onCountChanged: {
                            var i = find(newText)

                            if (i !== -1) {
                                currentIndex = i
                                validateFunc()
                            }

                            busyDialog.close()
                        }
                    }

                    Connections {
                        target: teams
                        function onLoaded() {
                            teamCombo.setTeam(root.model.teamId)
                            busyDialog.close()
                        }
                    }

                    ComboBox {
                        id: clearanceCombo
                        model: clearanceNames
                        Layout.minimumWidth: 160
                        onActivated: root.model.clearance = currentIndex + 1
                        currentIndex: root.model.clearance - 1
                    }

                    Component.onCompleted: companyCombo.setCompany(root.model.companyId)
                }
            }
        }
    }
}
