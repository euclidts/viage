import QtQuick 2.0

Flickable {
    leftMargin: 6
    rightMargin: 6
    topMargin: 3
    bottomMargin: 3
    anchors.fill: parent
    contentHeight: contentItem.childrenRect.height
    interactive: height < contentHeight
    clip: true
    boundsBehavior: Flickable.StopAtBounds
}
