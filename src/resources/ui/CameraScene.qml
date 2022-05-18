import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

import Complete

ColumnLayout {
    id: root
    anchors.fill: parent

    property string path
    property var onValidate

    CaptureSession {
        camera: Camera {
            id: camera

            onErrorOccurred: function(error, errorString) {
                if (Camera.NoError !== error) {
                    console.log("Camera error " + error + errorString)
                    root.parent.active = false
                }
            }
        }

        imageCapture: ImageCapture {
            id: imageCapture
            onImageSaved: console.log("Saved")
            onErrorOccurred: console.log(error + ' ' + message)
        }

        videoOutput: videoOutput
    }

    ColumnLayout {
        id: captureColumn

        VideoOutput {
            id: videoOutput
            Layout.fillHeight: true
            Layout.fillWidth: true
            Component.onCompleted: camera.start()
        }

        MaterialButton {
            text: qsTr("Scanner")
            icon.source: "qrc:/icons/camera.svg"
            onClicked: {
                imageCapture.capture()
                captureColumn.visible = false
                previewColumn.visible = true
            }
        }
    }

    ColumnLayout {
        id: previewColumn
        visible: false

        Image {
            id: preview
            Layout.fillHeight: true
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit
            source: imageCapture.preview
        }

        RowLayout {
            Layout.margins: 12

            MaterialButton {
                text: qsTr("Annuler")
                icon.source: "qrc:/icons/arrow-left.svg"
                onClicked: {
                    root.parent.active = false
                }
            }

            MaterialButton {
                text: qsTr("Scanner de nouveau")
                icon.source: "qrc:/icons/camera.svg"
                onClicked: {
                    previewColumn.visible = false
                    captureColumn.visible = true
                }
            }

            MaterialButton {
                text: qsTr("Valider")
                icon.source: "qrc:/icons/arrow-right.svg"
                onClicked: {
                    console.log(path)
                    imageCapture.saveToFile(path)
                    onValidate()
                    root.parent.active = false
                }
            }
        }
    }
}
