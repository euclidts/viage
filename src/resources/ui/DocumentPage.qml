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

    DocumentLisView {
        name: qsTr("Pieces d'identitee des parteniares")
        documentCategory: 0
        onEdit: function(list) {
            documents.id = list
        }
        urlFrom: urlProvider
        canEdit: editing
    }

//    onVisibleChanged: if (visible) checkCompeted()

//    function checkCompeted() {
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

//    Connections {
//        target: documents
//        function onTaxDeclarationChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onBuildingDetailsChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onPictureChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onInsuranceChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onBebChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onJobsChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    Connections {
//        target: documents
//        function onFutureJobsChanged() {
//            documentPage.checkCompeted()
//        }
//    }

//    FlickableItem {
//        BackgroundRect {
//            ColumnLayout {
//                width: availableWidth
//                Layout.minimumWidth: 200

//                ColumnLayout {
//                    spacing: 12
//                    Layout.margins: 12

//                    UrlLisView {
//                        name: qsTr("Pieces d'identitee des parteniares")
//                        listOf: documents.id
//                        onEdit: function(list) {
//                            documents.id = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Extrait du registre foncier")
//                        listOf: documents.registeryExcerpt
//                        onEdit: function(list) {
//                            documents.registeryExcerpt = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Extrait des poursuites")
//                        listOf: documents.pursuitExcerpt
//                        onEdit: function(list) {
//                            documents.pursuitExcerpt = list
//                        }
//                        urlFrom: urlProvider


//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Déclaration d'impôt")
//                        listOf: documents.taxDeclaration
//                        onEdit: function(list) {
//                            documents.taxDeclaration = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Détails concernant l'immeuble")
//                        listOf: documents.buildingDetails
//                        onEdit: function(list) {
//                            documents.buildingDetails = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Photo de l'objet")
//                        listOf: documents.picture
//                        onEdit: function(list) {
//                            documents.picture = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Assurance du batiment")
//                        listOf: documents.insurance
//                        onEdit: function(list) {
//                            documents.insurance = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Cas échéant / police détaillé de l'établissement ou le BEB")
//                        listOf: documents.beb
//                        onEdit: function(list) {
//                            documents.beb = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Descriptif / justificatifs des traveaux des 5 dernières années")
//                        listOf: documents.jobs
//                        onEdit: function(list) {
//                            documents.jobs = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }

//                    UrlLisView {
//                        name: qsTr("Descriptif des traveaux à prévoir / devis")
//                        listOf: documents.futureJobs
//                        onEdit: function(list) {
//                            documents.futureJobs = list
//                        }
//                        urlFrom: urlProvider
//                        canEdit: editing
//                    }
//                }
//            }
//        }
//    }
}
