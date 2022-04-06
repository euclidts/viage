import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtCore

import Data

ColumnLayout {
    spacing: 0
    Layout.margins: 6

    required property string name
    required property var listOf
    required property var onEdit
    required property var urlFrom
    property bool canEdit: true
    property bool completed: false

    Label {
        text: name
        font.bold: true
    }

    ListView {
        id: root
        interactive: false
        implicitHeight: contentHeight
        Layout.fillWidth: true

        property bool aquiring: false
        property bool fromCamera: false

        model: UrlsModel { list: listOf }

        delegate: RowLayout {
            spacing: 0
            width: root.width

            required property var model
            required property int index

            function aquire(url) {
                model.url = url
                onEdit(root.model.list)
            }

            Component.onCompleted: {
                if (root.aquiring) {
                    urlFrom.func = aquire

                    if (root.fromCamera) {
                        urlFrom.pictureName = StandardPaths.writableLocation(
                                    StandardPaths.DocumentsLocation)
                                + "/viage_"
                                + currentAccount.index
                                + '_'
                                + name
                                + '_'
                                + index
                                + ".jpeg"
                        urlFrom.camerLoader.active = true
                    } else { urlFrom.fileDialog.open() }

                    root.aquiring = false
                }
            }

            TextField {
                text: model.url
                readOnly: true
                Layout.fillWidth: true
                onTextChanged: text !== "" ? completed = true
                                           : completed = false
            }

            RoundButton {
                icon.source: "qrc:/icons/trash-alt.svg"
                onClicked: {
                    listOf.removeItems(model.index, model.index)
                    onEdit(root)
                }
            }
        }
    }

    RowLayout {
        RoundButton {
            icon.source: "qrc:/icons/file-pdf.svg"
            icon.width: height * 0.4
            onClicked: {
                root.aquiring = true
                root.fromCamera = false
                listOf.appendItems(1)
            }
        }

        RoundButton {
            icon.source: "qrc:/icons/camera.svg"
            onClicked: {
                root.aquiring = true
                root.fromCamera = true
                listOf.appendItems(1)
            }
        }
    }
}
