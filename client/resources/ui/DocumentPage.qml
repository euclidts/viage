import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import People
import Data

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    property bool completed: bridge.documentsCompleted

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: parent.width
                spacing: 12
                anchors.margins: 12

                DocumentListView {
                    id: photos
                    name: qsTr("Photo de l'objet")
                    documentCategory: 1 // Picture
                    documentsFrom: documents
                }

                DocumentListView {
                    id: passport
                    name: qsTr("Pièces d’identité des partenaires")
                    documentCategory: 2 // Passeport
                    documentsFrom: documents
                }

                DocumentListView {
                    id: registery
                    name: qsTr("Extrait du registre foncier")
                    documentCategory: 4 // RegisteryExcerpt
                    documentsFrom: documents
                }

                DocumentListView {
                    id: pursuit
                    name: qsTr("Extrait des poursuites")
                    documentCategory: 8 // PursuitExcerpt
                    documentsFrom: documents
                }

                DocumentListView {
                    id: tax
                    name: qsTr("Déclaration d'impôt")
                    documentCategory: 16 // TaxDeclaration
                    documentsFrom: documents
                }

                DocumentListView {
                    id: building
                    name: qsTr("Détails concernant l'immeuble")
                    documentCategory: 32 // BuildingDetails
                    documentsFrom: documents
                }

                DocumentListView {
                    id: insurance
                    name: qsTr("Assurance du bâtiment")
                    documentCategory: 64 // Insurance
                    documentsFrom: documents
                }

                DocumentListView {
                    id: lucidity
                    name: qsTr("Certificat médical de discernement")
                    documentCategory: 128 // Discernement
                    documentsFrom: documents
                }

                DocumentListView {
                    id: calculation
                    name: qsTr("Cacul de l'usufruit strictement personnel")
                    documentCategory: 2048 // Calculation
                    documentsFrom: documents
                }

                ColumnLayout {
                    spacing: 12
                    Layout.margins: 0
                    Layout.fillWidth: true
                    visible: bridge.ppe

                    Label {
                        text: qsTr("En cas de PPE")
                        Layout.margins: 6
                        font.bold: true
                    }

                    DocumentListView {
                        id: constitution
                        name: qsTr("Acte de constitution")
                        documentCategory: 16384
                        documentsFrom: documents
                    }

                    DocumentListView {
                        id: ppe
                        name: qsTr("Règlement PPE")
                        documentCategory: 32768
                        documentsFrom: documents
                    }

                    DocumentListView {
                        id: ppepvs
                        name: qsTr("3 derniers PV des assemblées générales de la PPE")
                        documentCategory: 65536
                        documentsFrom: documents
                    }
                }

                Label {
                    text: qsTr("Détails additionnels")
                    Layout.margins: 6
                    font.bold: true
                }

                DocumentListView {
                    id: maintenance
                    name: qsTr("Contrat(s) d'entretien")
                    documentCategory: 8192
                    documentsFrom: documents
                }

                DocumentListView {
                    id: jobs
                    name: qsTr("Descriptif / justificatifs des travaux des 5 dernières années")
                    documentCategory: 512
                    documentsFrom: documents
                }

                DocumentListView {
                    id: futurs
                    name: qsTr("Descriptif des travaux à prévoir / devis")
                    documentCategory: 1024
                    documentsFrom: documents
                }

                DocumentListView {
                    id: beb
                    name: qsTr("Cas échéant / police détaillée de l’établissement ou le BEB")
                    documentCategory: 256
                    documentsFrom: documents
                }

                DocumentListView {
                    id: other
                    name: qsTr("Autre")
                    documentCategory: 4096
                    documentsFrom: documents
                }
            }
        }
    }
}
