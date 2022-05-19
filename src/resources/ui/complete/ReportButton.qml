MaterialButton {
    visible: accountsPages.currentIndex < 1
             && rootStack.currentIndex === 0
    text: qsTr("Rapport")
    icon.source: "qrc:/icons/download.svg"
    onClicked: {
        urlProvider.func = function() {
            bridge.requestReport(urlProvider.path)
        }
        urlProvider.folderDialog.open()
    }
}
