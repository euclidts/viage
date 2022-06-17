import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

GroupBox {
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var dateOf
    property int maxYear: -70
    property string name: qsTr("Date de naissance")

    label: Label {
        text: name
        font.italic: true
    }

    GridLayout {
        columns: window.width < 400 ? 2 : 3

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
                onActivated: {
                    let date = dateOf.birthDay
                    date.setMonth(currentIndex)
                    dateOf.birthDay = date
                }
                currentIndex: dateOf.birthDay.getMonth()
            }
        }

        IntChooser {
            minimum: new Date().getFullYear() - 120
            maximum: new Date().getFullYear() + maxYear
            name: qsTr("Année")
            numberOf: dateOf.birthDay.getFullYear()
            onEdit: function(val) {
                let date = dateOf.birthDay
                date.setFullYear(val)
                dateOf.birthDay = date
            }
        }
    }
}
