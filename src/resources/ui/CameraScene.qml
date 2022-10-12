import QtQuick
import QtQuick.Controls
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

        imageCapture: imageCapture
        videoOutput: videoOutput
    }

    ImageCapture {
        id: imageCapture
        onErrorOccurred: console.log(error + ' ' + message)
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
        visible: false
        source: imageCapture.preview
    }

    ComboBox {
        Layout.fillWidth: true
        visible: videoOutput.visible
        textRole: "description"
        model: mediaDevices.videoInputs

        MediaDevices {
            id: mediaDevices
            Component.onCompleted: console.log(videoInputs)
        }
        onCurrentIndexChanged: camera.cameraDevice = mediaDevices.videoInputs[currentIndex]
    }

    RowLayout {
        Layout.margins: 12

        MaterialButton {
            text: qsTr("Annuler")
            icon.source: "qrc:/icons/arrow-left.svg"
            onClicked: root.parent.active = false
        }

        MaterialButton {
            id: scanButton
            text: qsTr("Scanner")
            icon.source: "qrc:/icons/camera.svg"
            visible: videoOutput.visible
            onClicked: {
                imageCapture.capture()
                videoOutput.visible = false
                preview.visible = true
            }
        }

        MaterialButton {
            id: rescanButton
            text: qsTr("Scanner de nouveau")
            icon.source: "qrc:/icons/camera.svg"
            visible: preview.visible
            onClicked: {
                videoOutput.visible = true
                preview.visible = false
            }
        }

        MaterialButton {
            id: validateButton
            text: qsTr("Valider")
            icon.source: "qrc:/icons/arrow-right.svg"
            visible: preview.visible
            onClicked: {
                imageCapture.saveToFile(path)
                onValidate()
                root.parent.active = false
            }
        }
    }
}
