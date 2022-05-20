import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

GroupBox {
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var dateOf
    property int maxYear: -65
    property bool editing: true
    property string name: qsTr("Date de naissance")

    label: Label {
        text: name
        font.italic: true
    }

    ColumnLayout {
        width: parent.width

        ColumnLayout {
            spacing: 0
            Layout.fillWidth: true
            visible: editing

            RowLayout {
                spacing: 0

                IntChooser {
                    name: qsTr("Jour")
                    minimum: 1
                    maximum: 31
                    numberOf: dateOf.birthDay.getDate()
                    onEdit: function(val) {
                        let date = dateOf.birthDay
                        date.setDate(val)
                        dateOf.birthDay = date
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
                            let date = dateOf.birthDay
                            date.setMonth(currentIndex)
                            dateOf.birthDay = date
                        }
                        currentIndex: dateOf.birthDay.getMonth()
                    }
                }
            }

            IntChooser {
                property int currentYear: new Date().getFullYear()

                minimum: currentYear - 120
                maximum: currentYear + maxYear
                name: qsTr("Année")
                numberOf: dateOf.birthDay.getFullYear()
                onEdit: function(val) {
                    let date = dateOf.birthDay
                    date.setFullYear(val)
                    dateOf.birthDay = date
                }
            }
        }

        TextField {
            text: Qt.formatDate(dateOf.birthDay, "dd.MM.yy")
            readOnly: true
            visible: !editing
            Layout.fillWidth: true
        }
    }
}
