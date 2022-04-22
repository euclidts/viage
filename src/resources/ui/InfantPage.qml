import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

import People

ListView {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    clip: true

    model : InfantModel { list: infants }

    property bool completed: false

    onCountChanged: busyDialog.close()

    delegate: BackgroundRect {
        id: infant

        required property var model
        required property int index
        property bool editing: true

        onVisibleChanged: if (visible) checkCompeted()

        function checkCompeted() {
            if (model.name === "") {
                infantPage.completed = false
                return
            } else if (model.surname === "") {
                infantPage.completed = false
                return
            } else if (model.phone === "") {
                infantPage.completed = false
                return
            }
            infantPage.completed = true
        }

        InfantDelegate {
            title: qsTr("Enfant")
            width: parent.width
            model: infant.model

            Connections {
                target: infantPage.model
                function onDataChanged(topLeft, bottomRight, roles) {
                    if (topLeft.row === model.index) {
                        infant.checkCompeted()
                    }
                }
            }

            Button {
                id: deleteButton
                icon.source: "qrc:/icons/trash-alt.svg"
                //                    visible: owner.editing && ownersPage.count > 1
                onClicked:
                    //                    if (!foucsOnEmpty())
                {
                    infants.removeItems(model.index, model.index)
                }
            }

            //        Button {
            //            text: qsTr("Modifier")
            //            highlighted: true
            //            Layout.margins: 12
            //            Layout.alignment: Qt.AlignRight
            //            visible: !infant.editing
            //            onClicked: {
            //                infant.editing = true
            //                infantrenPage.completed = false
            //            }
            //        }

            //        Button {
            //            id: validateButton
            //            highlighted: true
            //            text: qsTr("Valider")
            //            Layout.margins: 12
            //            Layout.alignment: Qt.AlignRight
            //            visible: infant.editing
            //            onClicked:
            //                //                    if (!foucsOnEmpty())
            //            {
            //                infant.editing = false
            //                infantPage.completed = true
            //                infants.validate(currentAccount.index)
            //                if (currentAccount.state < accountsPages.currentIndex)
            //                    currentAccount.state = accountsPages.getComplitionIndex()
            //            }
            //        }
        }
    }
}
