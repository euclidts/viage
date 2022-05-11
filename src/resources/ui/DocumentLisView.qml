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
    property var aquireFunc: function() {
        root.aquiring = true
        documentsFrom.addInWith(currentAccount.id, urlProvider.jsonMetadata)
        busyDialog.open()
    }

    function getPictureName(index : int) {
        return StandardPaths.writableLocation(
                    StandardPaths.DocumentsLocation)
                + "/viage/"
                + currentAccount.id
                + '/'
                + name
                + '_'
                + (index + 1)
                + ".jpeg"
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
            property var updateFunc: function() {
                model.relativePath = urlProvider.path
            }

            Component.onCompleted: {
                console.log("aquiring :" + root.aquiring)
                if (root.aquiring) {
                    model.relativePath = urlProvider.path
                    root.aquiring = false
                    busyDialog.close()
                }
            }

            TextField {
                id: flieName
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
                    urlProvider.path = getPictureName(index)
                    urlProvider.camerLoader.active = true
                }
            }

            RoundButton {
                icon.source: "qrc:/icons/download.svg"
                visible: model.isUploaded
                onClicked: {
                    urlProvider.func = function() {
                        bridge.downloadFile("documents/" + model.id + "/body",
                                            urlProvider.path,
                                            flieName.text)
                    }
                    urlProvider.folderDialog.open()
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
                urlProvider.path = getPictureName(root.count)
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
