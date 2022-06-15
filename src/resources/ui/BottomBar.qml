import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Dialogs

RowLayout {
    visible: false
    spacing: 0

    MaterialButton {
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
                 && bridge.clearance === 4
        text: qsTr("Conseillers")
        icon.source: "qrc:/icons/users.svg"
        icon.width: height * 0.6

        onClicked: rootStack.currentIndex = 1
    }

    MaterialButton {
        id: reportButton
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        text: qsTr("Rapport")
        icon.source: "qrc:/icons/download.svg"
        onClicked: {
            enabled = false
            bridge.requestReport()
        }

        Connections {
            target: bridge
            function onLoaded() { reportButton.enabled = true }
        }
    }

    MaterialButton {
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        text: qsTr("Calcul")
        icon.source: "qrc:/icons/calculator.svg"
        icon.width: height * 0.35
        onClicked: rootStack.currentIndex = 2
    }

    MaterialButton {
        text: qsTr("Onboarding")
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            bridge.onboard()
            contacts.clear()
            habitat.clear()
            exterior.clear()
        }
    }

    MaterialButton {
        text: qsTr("Ajouter un conseiller")
        visible: rootStack.currentIndex === 1
                 && usersPages.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            topBar.searchBar.text = ""
            hiring = true
            users.add()
        }
    }

    MaterialButton {
        visible: rootStack.currentIndex === 1
                 && usersPages.currentIndex === 0
        text: qsTr("Accueil")
        icon.source: "qrc:/icons/home.svg"

        onClicked: rootStack.currentIndex = 0
    }

    MaterialButton {
        text: accountsPages.currentIndex === 1 ? qsTr("Ajouter un partenaire")
                                               : qsTr("Ajouter un contact")
        visible: (accountsPages.currentIndex === 1
                 && owners.completed
                 && ownersPage.count < 2)
                 || (accountsPages.currentIndex === 2
                 && (contacts.completed || contactPage.count === 0))
        // exception for potentially empty contact list
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            accountsPages.currentIndex === 1 ? owners.addIn(bridge.accountId)
                                             : contacts.addIn(bridge.accountId)
        }
    }

    MaterialButton {
        id: continueButton
        text: accountsPages.currentIndex === 5 ? qsTr("Terminer")
                                               : qsTr("Continuer")

        visible: ( accountsPages.currentIndex > 0
                  && accountsPages.itemAt(accountsPages.currentIndex).completed )
                 || ( accountsPages.currentIndex === 2 &&
                     accountsPages.itemAt(accountsPages.currentIndex).count === 0 )
        // exception for potentially empty children list
        icon.source: accountsPages.currentIndex === 5 ? "qrc:/icons/arrow-left.svg"
                                                      : "qrc:/icons/arrow-right.svg"

        onClicked: {
            if (accountsPages.currentIndex === 5) {
                accountsPages.validateItem()
                accountsPages.currentIndex = 0
            } else {
                accountsPages.validateItem()
                accountsPages.loadItemAt(accountsPages.currentIndex + 1)
            }
        }
    }
}
