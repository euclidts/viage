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
        id: accountRow

        ColumnLayout {
            Layout.fillWidth: true

            Label {
                text: (acronym === "" ? id : acronym)
                      + " - " + Qt.formatDate(created, "dd.MM.yy")
            }

            Label {
                text: [
                    qsTr("Incomplet"),
                    qsTr("Signé"),
                    qsTr("Reçu"),
                    qsTr("Expertisé")
                ][Math.max(model.state - 7, 0)]
                + " - " + Qt.formatDate(modified, "dd.MM.yy");
            }
        }

        ColumnLayout {
            visible: !settingsDialog.invisible.checked
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight

            Label {
                text: habitat.street + ' ' + habitat.city + ' ' + habitat.zip + ' ' + habitat.canton
                font.bold: true
                visible: (habitat.street !== "")
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
            }

            Label {
                text: advisorFirstName + ' ' + advisorLastName + ' ' + company
                font.italic: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
            }
        }

        ListView {
            interactive: false
            implicitHeight: contentHeight
            implicitWidth: accountRow.width / 3
            Layout.alignment: Qt.AlignRight
            model: owners
            delegate: Label {
                required property var modelData
                required property int index
                text: modelData.firstName + ' ' + modelData.lastName
            }
            visible: !settingsDialog.invisible.checked
        }
    }

    onClicked: {
        currentAccount = model
        accountsPages.setComplitedPages()
        accountsPages.loadItem()
    }

    background: Rectangle {
        implicitHeight: Material.delegateHeight - 4
        radius: 4
        color: Material.background
        opacity: .8
    }

    Component.onCompleted: {
        currentAccount = model
        if (onboarding) {
            accountsPages.setComplitedPages()
            accountsPages.currentIndex = 1
        }
    }
}
