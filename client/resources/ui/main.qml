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

    readonly property bool portrait: width < 500

    readonly property var stateNames: [
        qsTr("Initialisé"),
        qsTr("Partenaires complétés"),
        qsTr("Contacts complétés"),
        qsTr("Habitat complété"),
        qsTr("Exterieur complété"),
        qsTr("Documents complétés"),
        qsTr("Réception du dossier \n par Viage SA"),
        qsTr("Transmission du dossier \n au CA de Viager Swiss SA"),
        qsTr("Expert immobilier"),
        qsTr("Décision du CA \n de Viager Swiss SA"),
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

    function onLogin (success: bool, error: string) {
        if (success) {
            rootStack.currentIndex = 0
            logginDialog.clear()
            busyDialog.close()
        }
        else {
            onExceptionAction(qsTr("Erreur d'authentification"),
                    error === "Host requires authentication" ?
                        qsTr("Mot de passe ou identifiant incorrect, essayez de nouveau ou contactez Viage pour recevoir un nouveau mot de passe")
                      : error,
                    function() { logginDialog.open() })
        }
    }

    function onException (prefix: string, error: string) {
        busyDialog.close()
        exceptionDialog.title = prefix
        exceptionDialog.text = error
        exceptionDialog.open()
    }

    function onExceptionAction (prefix: string, error: string, func, cancelable: bool) {
        if (typeof(func) !== 'undefined')
            exceptionDialog.func = func
        if (typeof(cancelable) !== 'undefined')
            exceptionDialog.cancelable = cancelable
        onException(prefix, error)
    }

    Image {
        id: backDrop
        source: "qrc:/images/vue_du_lac.jpg"
        anchors.centerIn: parent
        anchors.fill: parent
        clip: true
        fillMode: Image.PreserveAspectCrop

        Component.onCompleted: logginDialog.open()
    }

    ExceptionDialog { id: exceptionDialog }

    LoggInDialog { id: logginDialog }

    UrlProvider { id: urlProvider }

    SettingsDrawer { id: settingsDrawer }

    BusyDialog { id: busyDialog }

    Connections {
        target: bridge
        function onLoaded() { busyDialog.close() }
    }

    StackLayout {
        id: rootStack
        anchors.fill: parent
        currentIndex: 3

        onCurrentIndexChanged: topBar.searchBar.text = ""

        StackLayout {
            id: accountsPages

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
                } else {
                    bridge.getAccountDates()
                    accountsPages.currentIndex = 6;
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
                case 3:
                    habitat.validate(bridge.accountId)
                    break;
                case 4:
                    exterior.validate(bridge.accountId)
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

            ListView {
                Layout.fillWidth: true
                model: userModel
                delegate: UserDelegate {}
                onMovementStarted: topBar.searchBar.focus = false
                clip: true
                boundsBehavior: Flickable.StopAtBounds
            }

            Connections {
                target: selectedUser
                function onFilterRoleChanged() {
                    usersPages.currentIndex = 1
                }
            }

            UserPage { id: userPage }
        }

        CalculatorPage { id: calculatorPage }
    }

    header: TopBar { id: topBar }
    footer: BottomBar { id: bottomBar }
}
