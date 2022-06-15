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

    Material.theme: settingsDrawer.theme.checked ? Material.Light : Material.Dark
    Material.primary: "#3aaa35"
    Material.accent: "#3aaa35"

    font.pixelSize: 16

    property bool hiring: false
    readonly property var stateNames: [
        qsTr("Initialisé"),
        qsTr("Partenaires completés"),
        qsTr("Contactes completés"),
        qsTr("Habitat completés"),
        qsTr("Exterieur completés"),
        qsTr("Documents completés"),
        qsTr("Complet"),
        qsTr("Réception du dossier par Viage SA"),
        qsTr("Expert immobilier"),
        qsTr("Décision du CA de Viager Swiss SA"),
        qsTr("Rendez-vous chez le notaire"),
        qsTr("Paiement de la commission")
    ]

    readonly property var clearanceNames: bridge.clearance === 4
                                          ? [qsTr("Vendeur"),
                                             qsTr("Manager"),
                                             qsTr("Directeur"),
                                             qsTr("Administrateur")]
                                          : [qsTr("Vendeur"),
                                             qsTr("Manager"),
                                             qsTr("Directeur")]

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

    SettingsDrawer { id: settingsDrawer }

    StackLayout {
        id: rootStack
        anchors.fill: parent

        onCurrentIndexChanged: topBar.searchBar.text = ""

        StackLayout {
            id: accountsPages
            currentIndex: 0

            function loadItem() {
                busyDialog.open()

                if (!bridge.accountHasFlag(1)) {
                    owners.loadFrom(bridge.accountId)
                    return
                } else if (!bridge.accountHasFlag(2)) {
                    contacts.loadFrom(bridge.accountId)
                    return
                } else if (!bridge.accountHasFlag(4)) {
                    habitat.loadFrom(bridge.accountId)
                    return
                } else if (!bridge.accountHasFlag(8)) {
                    exterior.loadFrom(bridge.accountId)
                    return
                } else if (!bridge.accountHasFlag(16)) {
                    documents.loadFrom(bridge.accountId);
                    return
                } else if (!bridge.accountHasFlag(32)) {
                    accountsPages.currentIndex = 6;
                    busyDialog.close()
                    return
                }
            }

            function loadItemAt(index : int) {
                busyDialog.open()

                switch (index) {
                case 2:
                    contacts.loadFrom(bridge.accountId)
                    break
                case 3:
                    habitat.loadFrom(bridge.accountId)
                    break;
                case 4:
                    exterior.loadFrom(bridge.accountId)
                    break;
                case 5:
                    documents.loadFrom(bridge.accountId)
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
                    owners.validate(bridge.accountId)
                    break;
                case 2:
                    contacts.validate(bridge.accountId)
                    break;
                case 3:
                    habitat.validate(bridge.accountId)
                    break;
                case 4:
                    exterior.validate(bridge.accountId)
                    break;
                case 5:
                    documents.validate(bridge.accountId)
                    break;
                }
            }

            ListView {
                Layout.fillWidth: true
                model: accountModel
                delegate: AccountDelegate {}
                onMovementStarted: topBar.searchBar.focus = false
                clip: true
                boundsBehavior: Flickable.StopAtBounds
            }

            OwnersPage { id: ownersPage }
            ContactPage { id: contactPage }
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
                    ownersPage.positionViewAtBeginning()
                    accountsPages.currentIndex = 1
                    busyDialog.close()
                }
            }
            Connections {
                target: contacts
                function onLoaded() {
                    contactPage.positionViewAtBeginning()
                    accountsPages.currentIndex = 2
                    busyDialog.close()
                }
            }
            Connections {
                target: habitat
                function onLoaded() {
                    habitatPage.y = 0
                    accountsPages.currentIndex = 3
                    busyDialog.close()
                }
            }
            Connections {
                target: exterior
                function onLoaded() {
                    exteriorPage.y = 0
                    accountsPages.currentIndex = 4
                    busyDialog.close()
                }
            }
            Connections {
                target: documents
                function onLoaded() {
                    documentPage.y = 0
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
                onMovementStarted: topBar.searchBar.focus = false
                clip: true
                boundsBehavior: Flickable.StopAtBounds
            }

            Connections {
                target: bridge
                function onUserIdChanged() {
                    userModel.filterRole = bridge.userId
                    currentUser.filterRole = bridge.userId
                }
            }

            UserPage { id: userPage }
        }

        CalculatorPage { id: calculatorPage }
    }

    header: TopBar { id: topBar }
    footer: BottomBar { id: bottomBar }
}
