import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

GroupBox {
    Layout.topMargin: 12
    Layout.fillWidth: true

    required property var dateValue
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
            numberOf: dateValue ? dateValue.getDate() : 1
            // bypass Qt.locale()
            spin.textFromValue: (value, locale) => { return Number(value).toString() }
            onEdit: (val) => {
                let date = new Date(dateValue)
                date.setDate(val)
                dateValue = date
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
                    let date = new Date(dateValue)
                    date.setMonth(currentIndex)
                    dateValue = date
                    dateChanged(date)
                }
                currentIndex: dateValue ? dateValue.getMonth() : 0
            }
        }

        IntChooser {
            minimum: new Date().getFullYear() - 120
            maximum: new Date().getFullYear() + maxYear
            name: qsTr("Année")
            numberOf: dateValue ? dateValue.getFullYear() : minimum
            // bypass Qt.locale()
            spin.textFromValue: (value, locale) => { return Number(value).toString() }
            onEdit: (val) => {
                let d = new Date(dateValue)
                d.setFullYear(val)
                dateValue = d
                dateChanged(d)
            }
        }
    }
}
