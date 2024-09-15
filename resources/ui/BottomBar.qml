import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Dialogs

RowLayout {
    spacing: 0
    height: visibleChildren.length !== 0 ? 48 : 0

    Behavior on height { NumberAnimation { duration: 200 } }


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
        enabled: bridge.downloadProgress === -1.
        visible: (rootStack.currentIndex === 0 &&
                  (accountsPages.currentIndex === 0
                   || accountsPages.currentIndex === 6))
                 || rootStack.currentIndex === 2
        text: if (rootStack.currentIndex === 2 || accountsPages.currentIndex === 6)
                  qsTr("Document")
              else
                  qsTr("Rapport")
        icon.source: "qrc:/icons/download.svg"
        onClicked: if (accountsPages.currentIndex === 6)
                       bridge.requestAccount()
                   else if (rootStack.currentIndex === 2)
                       rent.writeToFile()
                   else
                       bridge.requestReport()
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
            accountModel.sortRole = 0
            topBar.searchBar.text = ""
            bridge.onboard()
            enabled = true // prevent double click
        }
    }

    MaterialButton {
        text: qsTr("Ajouter un conseiller")
        visible: rootStack.currentIndex === 1
                 && usersPages.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"
        onClicked: onExceptionAction(text,
                                     qsTr("Êtes-vous sûr de vouloir ajouter un nouveau conseiller ?"),
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
                     && (contacts.completed))
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
        icon.source: "qrc:/icons/arrow-right.svg"

        onClicked: {
            // exception for contacts
            accountsPages.currentIndex === 2 ? contacts.validate(bridge.accountId)
                                             : accountsPages.validateItem()
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
                       documents.validate(bridge.accountId)
                       accountsPages.currentIndex = 0
                   } else if (rootStack.currentIndex === 1) {
                       users.validate(selectedUser.filterRole)
                       usersPages.currentIndex = 0
                   }
    }

    MaterialButton {
        id: emailButton
        visible: (rootStack.currentIndex === 0
                  && accountsPages.currentIndex === 6)
                 && bridge.clearance === 4
        text: qsTr("e-mail")
        icon.source: "qrc:/icons/arrows-rotate.svg"
        onClicked: onExceptionAction(text,
                                     qsTr("Êtes-vous sûr de vouloir régénérer le document d'ouverture de dossier, et de le renvoyer par e-mail ?"),
                                     () => { bridge.requestEmail() }
                                     , true)
    }
}
