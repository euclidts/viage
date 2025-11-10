pragma Singleton
import QtQuick
import QtCore
import QtQuick.Controls 2.15
import QtQuick.Controls

QtObject {
    id:dataModel

    property ListModel seniorCitizens: ListModel {}
    property Dialog busyDialog
    property date transactionDate : new Date()
    property int valueBien : 1500000

    Component.onCompleted: {
        seniorCitizens.append({ sex: 0, birthDay: "1950/01/01" })
    }

    function getSeniorCitizensSingle(){
        return seniorCitizens.count === 1
    }

    function getPayload() {
        function sexToChar(sex) { return sex === 0 ? "M" : "F"; }
        var payload = {
            DateTransaction: Qt.formatDate(transactionDate, "yyyy/MM/dd"),
            ValeurBien: valueBien
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
        return payload
    }


    function getDocument(lang) {
        busyDialog.open()
        var payload = getPayload();
        payload.Lang = lang;
        bridge.requestUsufruitDocument(payload);

    }
}
