import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material

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
        qsTr("Réception du dossier par Viage SA "),
        qsTr("Expert immobilier"),
        qsTr("Décision du CA de Viager Swiss SA"),
        qsTr("Rendez-vous chez le notaire"),
        qsTr("Paiement de la commission")

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

        onStatusChanged: if (status === Image.Ready) {
                             logginDialog.open()
                         }
    }

    BusyDialog { id: busyDialog }

    LoggInDialog { id: logginDialog }

    UrlProvider { id: urlProvider }

    PhotoBooth { id: photoBooth }

    SettingsDialog { id: settingsDialog }

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
                busyDialog.open()

                if (!hasFlag(currentAccount.state, 1)) {
                    owners.loadFrom(currentAccount.id)
                    return
                } else if (!hasFlag(currentAccount.state, 2)) {
                    infants.loadFrom(currentAccount.id)
                    return
                } else if (!hasFlag(currentAccount.state, 4)) {
                    habitat.loadFrom(currentAccount.id)
                    return
                } else if (!hasFlag(currentAccount.state, 8)) {
                    exterior.loadFrom(currentAccount.id)
                    return
                } else if (!hasFlag(currentAccount.state, 16)) {
                    documents.loadFrom(currentAccount.id);
                    return
                } else if (!hasFlag(currentAccount.state, 32)) {
                    accountsPages.currentIndex = 6;
                    busyDialog.close()
                    return
                }
            }

            function loadItemAt(index : int) {
                busyDialog.open()

                switch (index) {
                case 2:
                    infants.loadFrom(currentAccount.id)
                    break
                case 3:
                    habitat.loadFrom(currentAccount.id)
                    break;
                case 4:
                    exterior.loadFrom(currentAccount.id)
                    break;
                case 5:
                    documents.loadFrom(currentAccount.id)
                    break;
                default:
                    accountsPages.currentIndex = index
                    busyDialog.close()
                    break;
                }
            }

            function validateItem() {
                switch (accountsPages.currentIndex) {
                case 1:
                    owners.validate(currentAccount.id)
                    break;
                case 2:
                    infants.validate(currentAccount.id)
                    break;
                case 3:
                    habitat.validate(currentAccount.id)
                    break;
                case 4:
                    exterior.validate(currentAccount.id)
                    break;
                case 5:
                    documents.validate(currentAccount.id)
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
                    busyDialog.close()
                }
            }
            Connections {
                target: infants
                function onLoaded() {
                    accountsPages.currentIndex = 2
                    busyDialog.close()
                }
            }
            Connections {
                target: habitat
                function onLoaded() {
                    accountsPages.currentIndex = 3
                    busyDialog.close()
                }
            }
            Connections {
                target: exterior
                function onLoaded() {
                    accountsPages.currentIndex = 4
                    busyDialog.close()
                }
            }
            Connections {
                target: documents
                function onLoaded() {
                    accountsPages.currentIndex = 5
                    busyDialog.close()
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

        CalculatorPage { id: calculatorPage }
    }

    header: TopBar { id: topBar }
    footer: BottomBar { id: bottomBar }
}
