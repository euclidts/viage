import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

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

    VideoOutput {
        id: videoOutput
        Layout.fillHeight: true
        Layout.fillWidth: true
        fillMode: Image.PreserveAspectFit
        Component.onCompleted: camera.start()
    }

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
            id: scanButton
            text: qsTr("Scanner")
            icon.source: "qrc:/icons/camera.svg"
            onClicked: {
                visible = false
                imageCapture.capture()
                videoOutput.visible = false
                preview.visible = true
            }
        }

        MaterialButton {
            id: rescanButton
            text: qsTr("Scanner de nouveau")
            icon.source: "qrc:/icons/camera.svg"
            visible: false
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
