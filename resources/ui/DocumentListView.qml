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
        urlProvider.jsonMetadata = jsonMetadata
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
                    model.localPath = bridge.uploadPath
                }

                Component.onCompleted: {
                    if (root.aquiring) {
                        root.aquiring = false
                        updateFunc()
                        busyDialog.close()
                    }
                }

                enabled: model.state !== 1 // Uploading

                GridLayout {
                    columns: 4
                    width: parent.width

                    FolderButton {
                        onClicked: {
                            urlProvider.func = updateFunc
                            bridge.getUploadFile()
                        }
                    }

                    RoundButton {
                        icon.source: "qrc:/icons/camera.svg"
                        onClicked: {
                            urlProvider.func = updateFunc
                            bridge.getPictureName(name, index)
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

                    ProgressBar {
                        Layout.columnSpan: 4
                        Layout.fillWidth: true
                        value: model.uploadProgress
                        visible: model.state === 1 // Uploading
                    }
                }
            }
        }

        FileDropRect {
            func: aquireFunc
            Layout.fillWidth: true

            RowLayout {
                spacing: 0

                FolderButton {
                    onClicked: {
                        urlProvider.func = aquireFunc
                        bridge.getUploadFile()
                    }
                }

                RoundButton {
                    icon.source: "qrc:/icons/camera.svg"
                    onClicked: {
                        urlProvider.func = aquireFunc
                        bridge.getPictureName(name, root.count)
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
