import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

ColumnLayout {
    id: root
    anchors.fill: parent

    property string pictureName
    property var onValidate

    CaptureSession {
        camera: Camera {
            id: camera

            onErrorOccurred: function(error, errorString) {
                if (Camera.NoError !== error) {
                    console.log("Camera.onError error " + error + " errorString " + errorString)
                    root.fatalError()
                }
            }
        }

        imageCapture: ImageCapture {
            id: imageCapture
            onImageSaved: console.log("Saved")
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

            Button {
                text: qsTr("Scanner de nouveau")
                highlighted: true
                onClicked: {
                    previewColumn.visible = false
                    captureColumn.visible = true
                }
            }

            Item { Layout.fillWidth: true }

            Button {
                highlighted: true
                text: qsTr("Valider")
                onClicked: {
                    imageCapture.saveToFile(pictureName)
                    onValidate(pictureName)
                    root.parent.active = false
                }
            }
        }
    }
}
