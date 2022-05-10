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
    required property var documentsFrom
    required property int documentCategory
    property bool canEdit: true
    property var jsonMetadata
    property var aquireFunc: function(json) {
        root.aquiring = true
        documentsFrom.addInWith(currentAccount.id, json)
    }

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

        model: DocumentFilterModel {
            sourceModel: DocumentModel { list: documents }
            category: documentCategory
        }

        delegate: RowLayout {
            spacing: 0
            width: root.width

            required property var model
            required property int index
            property var updateFunc: function(json) {
                // json arg for aquireFunc compatibility only
                model.relativePath = urlProvider.path
            }

            Component.onCompleted: {
                if (root.aquiring) {
                    model.relativePath = urlProvider.path
                    root.aquiring = false
                }
            }

            TextField {
                text: model.fileName + '.' + model.extension
                readOnly: true
                Layout.fillWidth: true
            }

            RoundButton {
                icon.source: "qrc:/icons/folder-open.svg"
                icon.width: height * 0.4
                onClicked: {
                    urlProvider.jsonMetadata = jsonMetadata
                    urlProvider.func = updateFunc
                    urlProvider.fileDialog.open()
                }
            }

            RoundButton {
                icon.source: "qrc:/icons/camera.svg"
                onClicked: {
                    urlProvider.jsonMetadata = jsonMetadata
                    urlProvider.func = updateFunc
                    urlProvider.path = StandardPaths.writableLocation(
                                StandardPaths.DocumentsLocation)
                            + "/viage/"
                            + currentAccount.id
                            + '/'
                            + name
                            + '_'
                            + (count + 1)
                            + ".jpeg"
                    urlProvider.camerLoader.active = true
                }
            }

            RoundButton {
                icon.source: "qrc:/icons/download.svg"
                onClicked: {
                }
            }

//            RoundButton {
//                icon.source: "qrc:/icons/trash-alt.svg"
//                onClicked: {
//                    listOf.removeItems(model.index, model.index)
//                }
//            }
        }
    }

    RowLayout {
        RoundButton {
            icon.source: "qrc:/icons/folder-open.svg"
            icon.width: height * 0.4
            onClicked: {
                urlProvider.jsonMetadata = jsonMetadata
                urlProvider.func = aquireFunc
                urlProvider.fileDialog.open()
            }
        }

        RoundButton {
            icon.source: "qrc:/icons/camera.svg"
            onClicked: {
                urlProvider.jsonMetadata = jsonMetadata
                urlProvider.func = aquireFunc
                urlProvider.path = StandardPaths.writableLocation(
                            StandardPaths.DocumentsLocation)
                        + "/viage/"
                        + currentAccount.id
                        + '/'
                        + name
                        + '_'
                        + (count + 1)
                        + ".jpeg"
                urlProvider.camerLoader.active = true
            }
        }
    }

    Component.onCompleted: {
        var txt = '{ "category" : '
                + documentCategory
                + ' }'
        jsonMetadata = JSON.parse(txt)
    }
}
