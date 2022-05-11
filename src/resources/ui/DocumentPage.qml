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

                    DocumentLisView {
                        id: photos
                        name: qsTr("Photo de l'objet")
                        documentCategory: 1
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: passport
                        name: qsTr("Pieces d'identité des parteniares")
                        documentCategory: 2
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: registery
                        name: qsTr("Extrait du registre foncier")
                        documentCategory: 3
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: pursuit
                        name: qsTr("Extrait des poursuites")
                        documentCategory: 4
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: tax
                        name: qsTr("Déclaration d'impôt")
                        documentCategory: 5
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: building
                        name: qsTr("Détails concernant l'immeuble")
                        documentCategory: 6
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: insurance
                        name: qsTr("Assurance du batiment")
                        documentCategory: 7
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: beb
                        name: qsTr("Cas échéant / police détaillé de l'établissement ou le BEB")
                        documentCategory: 8
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: jobs
                        name: qsTr("Descriptif / justificatifs des traveaux des 5 dernières années")
                        documentCategory: 9
                        documentsFrom: documents
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: futurs
                        name: qsTr("Descriptif des traveaux à prévoir / devis")
                        documentCategory: 10
                        documentsFrom: documents
                        canEdit: editing
                    }
                }
            }
        }
    }
}
