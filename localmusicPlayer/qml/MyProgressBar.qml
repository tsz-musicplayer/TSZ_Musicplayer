import QtQuick 2.0


//苏雪莲 进度条
Rectangle {
    id: root
    width: 420
    height: 40
    color: "transparent"

    Rectangle {
        id: line
        width: 320
        height: 5
        color: "#dba4ae"
        radius: 3
        anchors.centerIn: parent
        Rectangle {
            id: point
            width: 8
            height: 8
            color: "white"
            radius: 8
        }
    }

    Text {
        id: presentTime
        x: 13
        text: qsTr("00:00")
        anchors.verticalCenterOffset: 1
        font.pixelSize: 12
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        id: endTime
        x: 381
        text: qsTr("00:00")
        anchors.verticalCenterOffset: 1
        font.pixelSize: 12
        anchors.verticalCenter: parent.verticalCenter
    }
}
