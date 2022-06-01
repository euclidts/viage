import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import People
import Data

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool editing: true
    property bool completed: bridge.documentsCompleted

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: availableWidth
                Layout.minimumWidth: 200

                ColumnLayout {
                    id: root
                    spacing: 12
                    Layout.margins: 12

                    DocumentListView {
                        id: photos
                        name: qsTr("Photo de l'objet")
                        documentCategory: 1
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: passport
                        name: qsTr("Pièces d’identité des partenaires")
                        documentCategory: 2
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: registery
                        name: qsTr("Extrait du registre foncier")
                        documentCategory: 4
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: pursuit
                        name: qsTr("Extrait des poursuites")
                        documentCategory: 8
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: tax
                        name: qsTr("Déclaration d'impôt")
                        documentCategory: 16
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: building
                        name: qsTr("Détails concernant l'immeuble")
                        documentCategory: 32
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: insurance
                        name: qsTr("Assurance du bâtiment")
                        documentCategory: 64
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: beb
                        name: qsTr("Cas échéant / police détaillée de l’établissement ou le BEB")
                        documentCategory: 128
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: jobs
                        name: qsTr("Descriptif / justificatifs des travaux des 5 dernières années")
                        documentCategory: 256
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentListView {
                        id: futurs
                        name: qsTr("Descriptif des travaux à prévoir / devis")
                        documentCategory: 512
                        documentsFrom: documents
                        canEdit: editing
                    }
                }
            }
        }
    }
}
