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
    property bool completed: true

//    function checkCompeted() {

//        if (documentPage.completed) return

//        if (documents.id.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.registeryExcerpt.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.pursuitExcerpt.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.taxDeclaration.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.buildingDetails.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.picture.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.insurance.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.beb.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.jobs.empty()) {
//            documentPage.completed = false
//            return
//        } else if (documents.futureJobs.empty()) {
//            documentPage.completed = false
//            return
//        }
//        documentPage.completed = true
//    }

//    Connections {
//        target: documents
//        function onRegisteryExcerptChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onPursuitExcerptChanged() {
//            documentPage.checkCompeted()
//        }
//    }

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: availableWidth
                Layout.minimumWidth: 200

                ColumnLayout {
                    spacing: 12
                    Layout.margins: 12

                    DocumentLisView {
                        name: qsTr("Pieces d'identité des parteniares")
                        documentCategory: 1
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Extrait du registre foncier")
                        documentCategory: 2
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Extrait des poursuites")
                        documentCategory: 3
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Déclaration d'impôt")
                        documentCategory: 4
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Détails concernant l'immeuble")
                        documentCategory: 5
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Photo de l'objet")
                        documentCategory: 6
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Assurance du batiment")
                        documentCategory: 7
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Cas échéant / police détaillé de l'établissement ou le BEB")
                        documentCategory: 8
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Descriptif / justificatifs des traveaux des 5 dernières années")
                        documentCategory: 9
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }

                    DocumentLisView {
                        name: qsTr("Descriptif des traveaux à prévoir / devis")
                        documentCategory: 10
                        onEdit: function(list) {
                            documents.id = list
                        }
                        urlFrom: urlProvider
                        canEdit: editing
                    }
                }
            }
        }
    }
}
