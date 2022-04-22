import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Dialogs
import QtCore

RowLayout {
    visible: false
    spacing: 0

    MaterialButton {
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        text: qsTr("Conseillers")
        icon.source: "qrc:/icons/users.svg"
        icon.width: height * 0.6

        onClicked: rootStack.currentIndex = 1
    }


    FolderDialog {
        id: folderDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        onAccepted: bridge.requestReport(currentFolder)
    }

    MaterialButton {
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        text: qsTr("Rapport")
        icon.source: "qrc:/icons/file.svg"
        icon.width: height * 0.35

        onClicked: folderDialog.open()
    }

    MaterialButton {
        text: qsTr("Onboarding")
        visible: accountsPages.currentIndex < 1
                 && rootStack.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            topBar.searchBar.text = ""
            onboarding = true
            accounts.add()
        }
    }

    MaterialButton {
        text: qsTr("Ajouter un conseiller")
        visible: rootStack.currentIndex === 1
                 && usersPages.currentIndex === 0
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            topBar.searchBar.text = ""
            hiring = true
            users.appendItems(1)
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
        text: qsTr("Ajouter un partenaire")
        visible: accountsPages.currentIndex === 1
                 && ownersPage.completed
                 && ownersPage.count < 2
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            owners.addIn(currentAccount.index)
            ownersPage.completed = false
        }
    }

    MaterialButton {
        text: qsTr("Ajouter un enfant")
        visible: accountsPages.currentIndex === 2
                 && (infantPage.completed || infantPage.count === 0)
        // exception for potentially empty children list
        icon.source: "qrc:/icons/plus.svg"

        onClicked: {
            busyDialog.open()
            infants.addIn(currentAccount.index)
            infantPage.completed = false
        }
    }

    MaterialButton {
        id: continueButton
        text: qsTr("Continuer")
        visible: ( accountsPages.currentIndex > 0
                  && accountsPages.itemAt(accountsPages.currentIndex).completed )
                 || ( accountsPages.currentIndex === 2 &&
                     accountsPages.itemAt(accountsPages.currentIndex).count === 0 )
        // exception for potentially empty children list
        icon.source: "qrc:/icons/arrow-right.svg"

        onClicked: {
            accountsPages.validateItem()
            accountsPages.currentIndex++
        }
    }
}
