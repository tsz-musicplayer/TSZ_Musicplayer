import QtQuick 2.0
//苏雪莲
Rectangle {
    id: root
    width: 1000
    height: 60
    color: "pink"

    property int iconSize: 20

    property bool bPlaying: false
    property int nPlayIndex: 0
    Rectangle {
        id: iconRect
        anchors.verticalCenter: parent.verticalCenter
        width: 50
        height: 50
        color: "transparent"
        Image {
            id: iconImg
            source: "qrc:/images/music.png"
            width: 50
            height: 50
        }
    }
    Rectangle {
        id: searchRect
        x: 196
        width: 321
        height: 12
        color: "#dba4ae"
        radius: 6
        border.width: 0
        anchors.verticalCenterOffset: 0
        anchors.topMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        TextEdit {
            id: searchTextEdit
            width: 277
            height: 44
            color: "#f9f9f9"
            text: "点击搜索音乐"
            horizontalAlignment: Text.AlignLeft
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16

            Image {
                id: searchImg
                width: 30
                height: 30
                source: "../images/icon-search.png"
                anchors.left: searchTextEdit.right
                anchors.verticalCenter: parent.verticalCenter

                MouseArea {
                    id: searchSong
                    anchors.fill: parent
                    onPressed: {
                        searchImg.visible = false
                    }
                    onReleased: {
                        searchImg.visible = true
                    }
                    onClicked: {


                        //点击搜索音乐
                    }
                }
            }
        }
    }

    //退出
    Image {
        id: exitImg
        width: 30
        height: 30
        source: "../images/exit.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: root.right
        MouseArea {
            anchors.fill: parent
            onPressed: {
                exitImg.visible = false
            }
            onReleased: {
                exitImg.visible = true
            }
            onClicked: {
                Qt.quit()
            }
        }
    }
}
