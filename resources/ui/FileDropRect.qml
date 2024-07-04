import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    id: root
    height: childrenRect.height
    color: "transparent"

    required property var func

    DropArea {
        anchors.fill: parent

        onEntered: (drag) => {
                       root.color = "gray"
                       drag.accept(Qt.LinkAction)
                   }

        onDropped: (drop) => {
                       root.color = "transparent"
                       // Check valid extension as porposed in
                       var regExp = "^.*\.(pdf|PDF|png|PNG|jpg|JPG|jpeg|JPEG|raw|tiff|odt|doc|docx|xls|xlsx)(?:$|[#?])"
                       if (drop.urls[0].toString().match(regExp)) {
                           urlProvider.path = drop.urls[0]
                           func()
                       } else {
                           onException(qsTr("Chemin de fichier incorrect"),
                                       qsTr("Assurez vous que le fichier selectioné possède l'extension pdf, PDF, png, PNG, jpg, JPG, jpeg, JPEG, raw, tiff, odt, doc, docx, xls ou xlsx"))
                       }
                   }

        onExited: root.color = "transparent"
    }
}
