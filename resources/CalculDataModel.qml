pragma Singleton
import QtQuick
import QtCore
import QtQuick.Controls 2.15
QtObject {
    id:dataModel

    property ListModel seniorCitizens: ListModel {}


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

    function calculer(callback_good,callback_bad=function(status,r){console.error("call calculer",status,r)}){
        if (seniorCitizens.count < 1 || seniorCitizens.count > 2) {
            console.error("Il faut 1 ou 2 partenaires.")
            return
        }
        var payload = getPayload()
        var xhr = new XMLHttpRequest()
        xhr.open("POST", "https://viagetestrive.euclidtradingsystems.com/Account/Usufruit/Calcul?format=json")
        xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8")
        xhr.setRequestHeader("Accept", "application/json")

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status >= 200 && xhr.status < 300) {
                    var result = JSON.parse(xhr.responseText)
                    callback_good(result)
                } else {
                    callback_bad(xhr.status, xhr.responseText)
                }
            }
        }
        xhr.send(JSON.stringify(payload))
    }

function getDocument(lang = "French") {
    var payload = getPayload();
    payload.Lang = lang;

    var url = "https://viagetestrive.euclidtradingsystems.com/Account/Usufruit/Calcul?format=json";
    var headers = [
        { key: "Content-Type", value: "application/json" },
        { key: "Accept", value: "application/vnd.openxmlformats-officedocument.wordprocessingml.document" }
    ];

    if (Qt.platform.os === "wasm") {
        var xhr = new XMLHttpRequest();
        xhr.open("POST", url, true);
        xhr.responseType = "blob";
        headers.forEach(h => xhr.setRequestHeader(h.key, h.value));

        xhr.onload = function() {
            if (xhr.status === 200) {
                var url = js.globalThis.URL.createObjectURL(xhr.response);
                var a = js.globalThis.document.createElement('a');
                a.href = url;
                a.download = "monfichier.docx";
                js.globalThis.document.body.appendChild(a);
                a.click();
                js.globalThis.document.body.removeChild(a);
                js.globalThis.URL.revokeObjectURL(url);
                console.log("Fichier reçu avec succès !");
            } else {
                console.log("Erreur HTTP : " + xhr.status);
            }
        };

        xhr.onerror = function() {
            console.log("Erreur réseau lors de la requête POST");
        };

        xhr.send(JSON.stringify(payload));
    } else {
        var request = new XMLHttpRequest();
        request.open("POST", url);
        headers.forEach(h => request.setRequestHeader(h.key, h.value));
        request.responseType = "arraybuffer";

        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status === 200) {

                    var data = new Uint8Array(request.response);
                    var path = StandardPaths.writableLocation(StandardPaths.DownloadLocation) + "/calcul.docx";
                    var file = new File(path);
                    if (file.open(File.WriteOnly)) {
                        file.write(data);
                        file.close();
                        console.log("Fichier sauvegardé :", path);
                    } else {
                        console.log("Impossible d'ouvrir le fichier pour écriture");
                    }
                } else {
                    console.log("Erreur HTTP native :", request.status);
                }
            }
        };

        request.send(JSON.stringify(payload));
    }
}
}
