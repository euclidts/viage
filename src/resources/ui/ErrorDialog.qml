import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Dialog {
    modal: true
    closePolicy: Popup.NoAutoClose
    background.opacity: .8
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    implicitWidth: parent.width * 0.6

    property var func: function () {}
    property alias text: textLabel.text
    property bool cancelable: false

    function onClose() {
        func = function () {}
        cancelable = false
        errorDialog.close()
    }

    contentItem: ColumnLayout {
        spacing: 15

        Label {
            id: textLabel
            Layout.fillWidth: true
            wrapMode: Text.Wrap
        }

        RowLayout {
            Layout.fillWidth: true

            RoundButton {
                text: qsTr("Valider")
                Layout.fillWidth: true
                font.capitalization: Font.MixedCase
                font.bold: true
                highlighted: true
                onClicked: {
                    func()
                    onClose()
                }
            }

            RoundButton {
                text: qsTr("Annuler")
                visible: cancelable
                Layout.fillWidth: true
                font.capitalization: Font.MixedCase
                font.bold: true
                highlighted: true
                onClicked: onClose()
            }
        }
    }
}

