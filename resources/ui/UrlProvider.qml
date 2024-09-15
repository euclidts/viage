import QtQuick
import QtQuick.Dialogs
import QtCore
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

Rectangle {
    id: root
    anchors.centerIn: parent
    anchors.fill: parent
    visible: active
    color: "transparent"

    property var func
    property bool active: false

    onActiveChanged:
        if (active) {
            topBar.visible = false
            rootStack.visible = false
            bottomBar.visible = false
        } else {
            topBar.visible = true
            rootStack.visible = true
            bottomBar.visible = true
        }

    ColumnLayout {
        anchors.fill: parent

        CaptureSession {
            camera: Camera {
                id: camera
                active: root.active

                onErrorOccurred: function(error, errorString) {
                    if (Camera.NoError !== error) {
                        console.log("Camera error " + error + errorString)
                        root.active = false
                    }
                }
            }

            imageCapture: ImageCapture {
                id: imageCapture
                onErrorOccurred: console.log("ImageCapture error " + error + ' ' + message)
            }

            videoOutput: videoOutput
        }

        VideoOutput {
            id: videoOutput
            Layout.fillHeight: true
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: preview
            Layout.fillHeight: true
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit
            visible: false
            source: imageCapture.preview
        }

        RowLayout {
            Layout.margins: 12

            MaterialButton {
                text: qsTr("Annuler")
                icon.source: "qrc:/icons/arrow-left.svg"
                onClicked: root.active = false
            }

            ComboBox {
                Layout.fillWidth: true
                visible: videoOutput.visible
                textRole: "description"
                model: mediaDevices.videoInputs

                MediaDevices { id: mediaDevices }

                onCurrentIndexChanged: camera.cameraDevice = mediaDevices.videoInputs[currentIndex]
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
                    imageCapture.saveToFile(bridge.uploadPath)
                    func()
                    root.active = false
                }
            }
        }
    }
}
