import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtCore

import Data
import People
import Places
import Interface

ApplicationWindow {
    id: window
    visible: true
    title: "Viage"
    width: 1024
    height: 768

    Material.theme: settingsDialog.theme.checked ? Material.Light : Material.Dark
    Material.primary: "#3aaa35"
    Material.accent: "#3aaa35"

    font.pixelSize: 16

    property var currentAccount
    property var currentUser
    property bool onboarding: false
    property bool hiring: false
    readonly property var stateNames: [
        qsTr("Incomplet"),
        qsTr("Envoyé"),
        qsTr("En attente d'expertise"),
        qsTr("Expertisé")
    ]

    function onLogin (success: bool) {
        if (success) {
            topBar.visible = true
            bottomBar.visible = true
            logginDialog.close()
        }
        else {
            busyDialog.close()
            logginDialog.currentState = "error"
        }
    }

    function hasFlag (value: int, flag: int) {
        return (value & flag) === flag
    }

    Image {
        id: backDrop
        source: "qrc:/images/vue_du_lac.jpg"
        anchors.centerIn: parent
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop

        onStatusChanged: if (status === Image.Ready)
                             logginDialog.open()
    }

    BusyDialog { id: busyDialog }

    LoggInDialog { id: logginDialog }

    Rectangle {
        id: urlProvider
        anchors.centerIn: parent
        anchors.fill: parent
        visible: false
        color: "transparent"

        property alias fileDialog: fileDialog
        property alias camerLoader: cameraLoader
        property string pictureName
        property var func

        FileDialog {
            id: fileDialog
            currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
            nameFilters: ["(*.pdf *.png *.jpg *.jpeg *.raw *.tiff)", "(*)"]
            onAccepted: urlProvider.func(selectedFile)
        }

        Loader {
            id: cameraLoader
            anchors.fill: parent
            source: "qrc:/ui/CameraScene.qml"
            active: false

            onActiveChanged:
                if (active) {
                    urlProvider.visible = true
                    item.onValidate = urlProvider.func
                    item.pictureName = urlProvider.pictureName
                    topBar.visible = false
                    rootStack.visible = false
                    bottomBar.visible = false
                } else {
                    urlProvider.visible = false
                    topBar.visible = true
                    rootStack.visible = true
                    bottomBar.visible = true
                }
        }
    }

    SettingsDialog {
        id: settingsDialog
        x: Math.round((parent.width - width) / 2)
        y: 120
        implicitWidth: 270
    }

    StackLayout {
        id: rootStack
        anchors.fill: parent

        onCurrentIndexChanged: currentIndex < 1 ?
                                   accountModel.setFilterFixedString(topBar.searchBar.text)
                                 : userModel.setFilterFixedString(topBar.searchBar.text)

        StackLayout {
            id: accountsPages
            currentIndex: 0

            function loadItem() {
                if (!hasFlag(currentAccount.state, 1)) {
                    owners.loadFrom(currentAccount.index)
                    return
                } else if (!hasFlag(currentAccount.state, 2)) {
                    infants.loadFrom(currentAccount.index)
                    return
                } else if (!hasFlag(currentAccount.state, 4)) {
                    habitat.loadFrom(currentAccount.index)
                    return
                } else if (!hasFlag(currentAccount.state, 8)) {
                    exterior.loadFrom(currentAccount.index)
                    return
                } else if (!hasFlag(currentAccount.state, 16)) {
                    documents.loadFrom(currentAccount.index);
                    return
                } else if (!hasFlag(currentAccount.state, 32)) {
                    accountsPages.currentIndex = 6;
                    return
                }
            }

            function validateItem() {
                switch (accountsPages.currentIndex) {
                case 1:
                    owners.validate(currentAccount.index)
                    break;
                case 2:
                {
                    infantPage.completed = true
                    // exception for potentially empty children list
                    infants.validate(currentAccount.index)
                    break;
                }
                case 3:
                    habitat.validate(currentAccount.index)
                    break;
                case 4:
                    exterior.validate(currentAccount.index)
                    break;
                case 5:
                    documents.validate(currentAccount.index)
                    break;
                }
            }

            ListView {
                Layout.fillWidth: true
                model: accountModel
                delegate: AccountDelegate {}
                onMovementStarted: topBar.searchBar.focus = false
                clip: true
            }

            OwnersPage { id: ownersPage }
            InfantPage { id: infantPage }
            HabitatPage { id: habitatPage }
            ExteriorPage { id: exteriorPage }
            DocumentPage { id: documentPage }
            StatePage { id: statePage }

            Connections {
                target: accounts
                function onLoaded() { busyDialog.close() }
            }
            Connections {
                target: owners
                function onLoaded() {
                    accountsPages.currentIndex = 1
                }
            }
            Connections {
                target: infants
                function onLoaded() {
                    accountsPages.currentIndex = 2
                }
            }
            Connections {
                target: habitat
                function onLoaded() {
                    accountsPages.currentIndex = 3
                }
            }
            Connections {
                target: exterior
                function onLoaded() {
                    accountsPages.currentIndex = 4
                }
            }
            Connections {
                target: documents
                function onLoaded() {
                    accountsPages.currentIndex = 5
                }
            }
        }

        StackLayout {
            id: usersPages
            clip: true

            ListView {
                Layout.fillWidth: true
                model: userModel
                delegate: UserDelegate {}
            }

            UserPage { id: userPage }
        }
    }

    header: TopBar { id: topBar }
    footer: BottomBar { id: bottomBar }
}
