import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

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

    Label {
        Layout.fillWidth: true
        text: name
        font.bold: true
        wrapMode: Text.Wrap
    }

    ListView {
        id: root
        interactive: false
        implicitHeight: contentHeight
        Layout.fillWidth: true
        onCountChanged: positionViewAtEnd()

        property bool aquiring: false

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
                if (root.aquiring) {
                    root.aquiring = false
                    updateFunc()
                    busyDialog.close()
                }
            }

            TextField {
                id: flieName
                text: model.fileName + '.' + model.extension
                readOnly: true
                Layout.fillWidth: true
            }

            FolderButton {
                onClicked: {
                    urlProvider.func = updateFunc
                    urlProvider.fileDialog.open()
                }
            }

            RoundButton {
                icon.source: "qrc:/icons/camera.svg"
                onClicked: {
                    urlProvider.func = updateFunc
                    urlProvider.path = bridge.getPictureName(currentAccount.id,
                                                             name,
                                                             index)
                    urlProvider.loader.active = true
                }
            }

            RoundButton {
                icon.source: "qrc:/icons/trash-alt.svg"
                onClicked: {
                    listOf.remove(model.id)
                }
            }
        }
    }

    RowLayout {
        FolderButton {
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
                urlProvider.path = bridge.getPictureName(currentAccount.id,
                                                         name,
                                                         root.count)
                urlProvider.loader.active = true
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
