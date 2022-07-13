import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import Data

GroupBox {
    label: Label {
        Layout.fillWidth: true
        text: name
        font.bold: true
        wrapMode: Text.Wrap
    }
    Layout.margins: 12
    Layout.fillWidth: true
    contentHeight: contentItem.childrenRect.height

    required property string name
    required property var documentsFrom
    required property int documentCategory
    property var jsonMetadata
    property var aquireFunc: function() {
        root.aquiring = true
        documentsFrom.addInWith(bridge.accountId, urlProvider.jsonMetadata)
        busyDialog.open()
    }

    ColumnLayout {
        width: parent.width
        spacing: 0

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

            delegate: FileDropRect {
                func: updateFunc
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

                RowLayout {
                    spacing: 0
                    width: parent.width

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
                            urlProvider.path = bridge.getPictureName(name, index)
                            urlProvider.loader.active = true
                        }
                    }

                    TextField {
                        id: flieName
                        text: model.fileName + '.' + model.extension
                        readOnly: true
                        Layout.fillWidth: true
                    }

                    RoundButton {
                        icon.source: "qrc:/icons/trash-alt.svg"
                        onClicked: {
                            documentsFrom.remove(model.id)
                        }
                    }
                }
            }
        }

        FileDropRect {
            func: aquireFunc
            width: root.width

            RowLayout {
                spacing: 0

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
                        urlProvider.path = bridge.getPictureName(name, root.count)
                        urlProvider.loader.active = true
                    }
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
}
