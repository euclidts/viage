import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ItemDelegate {
    width: parent.width
    leftInset: 6
    rightInset: 6
    topInset: 3
    bottomInset: 3

    contentItem: RowLayout {

        Label {
            text: model.name + ' ' + model.surname
            Layout.fillWidth: true
        }

        Label {
            text: model.company
            font.bold: true
            Layout.fillWidth: true
        }
    }

    Component.onCompleted: {
        currentAdvisor = model
        if (hiring) {
            advisorsPages.currentIndex = 1
            hiring = false
        }
    }

    onClicked: {
        currentAdvisor = model
        advisorsPages.currentIndex = 1
    }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: Material.background
    }
}
