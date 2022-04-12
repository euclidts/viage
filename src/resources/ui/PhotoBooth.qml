import QtQuick
import QtMultimedia

Item {
    id: root
    width: parent.width

    signal fatalError

    CaptureSession {
        camera: Camera {
            id: camera

            onErrorOccurred: function(error, errorString) {
                if (Camera.NoError !== error) {
                    console.log("CameraItem.onError error " + error + " errorString " + errorString)
                    root.fatalError()
                }
            }
        }

        imageCapture: ImageCapture {
            id: imageCapture
        }
        videoOutput: videoOutput
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: imageCapture.capture();
        }
    }

    Image {
        id: photoPreView
        source: imageCapture.preview
    }

    function start() { camera.start() }
    function stop() { camera.stop() }
}
