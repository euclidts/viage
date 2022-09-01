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
                       var regExp = "[?:[a-zA-Z0-9-_\.]+(?:.pdf|.png|.jpg|.jpeg|.raw|.tiff)"
                       if (drop.urls[0].toString().match(regExp)) {
                           urlProvider.path = drop.urls[0]
                           func()
                       } else {
                           onException(qsTr("Chemin de fichier incorrect"),
                                       qsTr("Assurez vous que le fichier selectioné possède l'extension pdf, png, jpg, jpeg, raw ou tiff"))
                       }
                   }

        onExited: root.color = "transparent"
    }
}
