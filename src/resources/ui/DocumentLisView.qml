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
    required property var createFunc
    required property int documentCategory
    property bool canEdit: true
    property bool completed: false
    property alias count: root.count

    function makeJson () {
        var txt = '{ "category" : '
                + documentCategory
                + ' }'
        return JSON.parse(txt)
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

            Component.onCompleted: {
                if (root.aquiring) {
                    model.url = urlProvider.path
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
//                    listOf.removeItems(model.index, model.index)
                }
            }
        }
    }

    RowLayout {
        RoundButton {
            icon.source: "qrc:/icons/folder-open.svg"
            icon.width: height * 0.4
            onClicked: {
                root.aquiring = true
                urlProvider.func = createFunc(makeJson())
                urlProvider.fileDialog.open()
            }
        }

        RoundButton {
            icon.source: "qrc:/icons/camera.svg"
            onClicked: {
                root.aquiring = true
                urlProvider.func = createFunc(makeJson())
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
}
