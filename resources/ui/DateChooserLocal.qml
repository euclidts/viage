import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

GroupBox {
    Layout.topMargin: 12
    Layout.fillWidth: true

    property date birthDay : new Date()
    property int maxYear: -70
    property string name: qsTr("Date de naissance")

    label: Label {
        text: name
        font.italic: true
    }
    signal dateChanged(date newDate)
    GridLayout {
        columns: portrait ? 2 : 3

        IntChooser {
            name: qsTr("Jour")
            minimum: 1
            maximum: 31
            numberOf: birthDay.getDate()
            // bypass Qt.locale()
            spin.textFromValue: (value, locale) => { return Number(value).toString() }
            onEdit: (val) => {
                let date = new Date(birthDay)
                date.setDate(val)
                birthDay = date
                dateChanged(date)
            }
        }

        ColumnLayout {
            Label {
                text: qsTr("Mois")
                Layout.topMargin: 2
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
                    let date = new Date(birthDay)
                    date.setMonth(currentIndex)
                    birthDay = date
                    dateChanged(date)
                }
                currentIndex: birthDay.getMonth()
            }
        }

        IntChooser {
            minimum: new Date().getFullYear() - 120
            maximum: new Date().getFullYear() + maxYear
            name: qsTr("Année")
            numberOf: birthDay.getFullYear()
            // bypass Qt.locale()
            spin.textFromValue: (value, locale) => { return Number(value).toString() }
            onEdit: (val) => {
                let d = new Date(birthDay)
                d.setFullYear(val)
                birthDay = d
                dateChanged(d)
            }
        }
    }
}
