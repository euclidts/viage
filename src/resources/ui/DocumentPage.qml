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
    property bool completed: false

    FlickableItem {
        BackgroundRect {
            ColumnLayout {
                width: availableWidth
                Layout.minimumWidth: 200

                ColumnLayout {
                    id: root
                    spacing: 12
                    Layout.margins: 12

                    function checkCompleted() {

                        if (photos.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (passport.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (registery.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (pursuit.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (tax.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (building.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (insurance.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (beb.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (jobs.connt === 0) {
                            documentPage.completed = false
                            return
                        } else if (futurs.connt === 0) {
                            documentPage.completed = false
                            return
                        }

                        documentPage.completed = true
                    }

                    Connections {
                        target: documents
                        function onPostItemsAppended() {
                            root.checkCompleted()
                        }
                    }

                    Connections {
                        target: documents
                        function onPostItemsRemoved() {
                            root.checkCompleted()
                        }
                    }

                    DocumentLisView {
                        id: photos
                        name: qsTr("Photo de l'objet")
                        documentCategory: 1
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: passport
                        name: qsTr("Pieces d'identité des parteniares")
                        documentCategory: 2
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: registery
                        name: qsTr("Extrait du registre foncier")
                        documentCategory: 3
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: pursuit
                        name: qsTr("Extrait des poursuites")
                        documentCategory: 4
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: tax
                        name: qsTr("Déclaration d'impôt")
                        documentCategory: 5
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: building
                        name: qsTr("Détails concernant l'immeuble")
                        documentCategory: 6
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: insurance
                        name: qsTr("Assurance du batiment")
                        documentCategory: 7
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: beb
                        name: qsTr("Cas échéant / police détaillé de l'établissement ou le BEB")
                        documentCategory: 8
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: jobs
                        name: qsTr("Descriptif / justificatifs des traveaux des 5 dernières années")
                        documentCategory: 9
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }

                    DocumentLisView {
                        id: futurs
                        name: qsTr("Descriptif des traveaux à prévoir / devis")
                        documentCategory: 10
                        createFunc: function(json) {
                            documents.addInWith(currentAccount.id, json)
                        }
                        canEdit: editing
                    }
                }
            }
        }
    }
}
