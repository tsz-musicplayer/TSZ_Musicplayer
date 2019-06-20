import QtQuick 2.0
//苏雪莲 菜单按钮
Rectangle {
    id: root
    property alias picSource: pic.source
    property alias text: word.text
    property bool select: false

    signal clicked

    color: "pink"
    height: 50
    width: parent.width

    Image {
        id: pic
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        x: pic.x + 50
        id: word
        anchors.verticalCenter: parent.verticalCenter //垂直居中
        color: "white"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        id: ma
        anchors.rightMargin: -142
        anchors.fill: parent
        onClicked: {
            root.clicked()
            //root.color = select ? "#dba4ae" : "pink"
        }
        onPressed: {
            select = true
            root.color = "#dba4ae"
        }
        onReleased: {
            root.color = "pink"
        }
    }
}
