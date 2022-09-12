import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Dialogs

RowLayout {
    spacing: 0
    height: visibleChildren.length !== 0 ? 48 : 0

    Behavior on height {
        NumberAnimation { duration: 200 }
    }

    MaterialButton {
        visible: accountsPages.currentIndex === 0
                 && rootStack.currentIndex === 0
                 && bridge.clearance === 4
        text: qsTr("Conseillers")
        icon.source: "qrc:/icons/users.svg"
        icon.width: height * 0.6

        onClicked: rootStack.currentIndex = 1
    }

    MaterialButton {
        id: reportButton
        visible: (accountsPages.currentIndex === 0
                  && rootStack.currentIndex === 0)
                 || rootStack.currentIndex === 2
        text: rootStack.currentIndex === 2 ? qsTr("Document")
                                           : qsTr("Rapport")
        icon.source: "qrc:/icons/download.svg"
        onClicked: rootStack.currentIndex !== 2 ? bridge.requestReport()
                                                : rent.writeToFile()
    }

    MaterialButton {
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        text: qsTr("Calcul")
        icon.source: "qrc:/icons/calculator.svg"
        icon.width: height * 0.35
        onClicked: {
            rent.clear()
            rootStack.currentIndex = 2
        }
    }

    MaterialButton {
        text: qsTr("Onboarding")
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            enabled = false
            busyDialog.open()
            bridge.onboard()
            contacts.clear()
            habitat.clear()
            exterior.clear()
            enabled = true // prevent double click
        }
    }

    MaterialButton {
        text: qsTr("Ajouter un conseiller")
        visible: rootStack.currentIndex === 1
                 && usersPages.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: onExceptionAction(text,
                                 "Êtes-vous sûr de vouloir ajouter un nouveau conseiller",
                                 () => {
                                     busyDialog.open()
                                     bridge.hire()
                                 }, true)
    }

    MaterialButton {
        visible: (rootStack.currentIndex === 1
                  && usersPages.currentIndex === 0)
                 || rootStack.currentIndex === 2
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
        text: qsTr("Continuer")

        visible: (accountsPages.currentIndex > 0
                  && accountsPages.currentIndex < 5
                  && accountsPages.itemAt(accountsPages.currentIndex).completed)
                 || ( accountsPages.currentIndex === 2 &&
                     accountsPages.itemAt(accountsPages.currentIndex).count === 0)
        // exception for potentially empty children list
        icon.source: "qrc:/icons/arrow-right.svg"

        onClicked: {
            accountsPages.validateItem()
            accountModel.sortRole = 0
            topBar.searchBar.text = ""
            accountsPages.loadItemAt(accountsPages.currentIndex + 1)
        }
    }

    MaterialButton {
        id: finishButton
        text: qsTr("Terminer")

        visible: accountsPages.currentIndex === 5 && accountsPages.itemAt(5).completed
                 || usersPages.currentIndex === 1 && userPage.completed
        icon.source: "qrc:/icons/arrow-left.svg"

        onClicked: if (rootStack.currentIndex === 0) {
                       accountsPages.validateItem()
                       accountsPages.currentIndex = 0
                   } else if (rootStack.currentIndex === 1) {
                       users.validate(selectedUser.filterRole)
                       usersPages.currentIndex = 0
                   }
    }
}
