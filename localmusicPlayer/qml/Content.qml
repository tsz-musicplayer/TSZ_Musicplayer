import QtQuick 2.0
import QtMultimedia 5.8
//苏雪莲 菜单
Rectangle {
    color: "#fcfcfc"
    width: parent.width
    //    width: 300
    //    height: 400
    Column {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        Text {
            text: qsTr("我的音乐")
            font.pixelSize: 16
        }
        MenuButton {
            y: 20
            id: findMusicButton
            picSource: "qrc:/images/icon-music.png"
            text: qsTr("本地音乐")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.color = select ? "#dba4ae" : "pink"
                    //显示我的音乐界面
                }
            }
        }
        MenuButton {
            y: 100
            id: downloadButton
            picSource: "qrc:/images/download.png"
            text: qsTr("下载音乐")
        }
        Text {
            text: qsTr("  ")
            font.pixelSize: 16
        }



        Text {
            id:label
            text: qsTr("我的歌单")
            font.pixelSize: 16
        }


        MenuButton {
            y: 20
            id: enjoyMusicButton
            picSource: "qrc:/images/enjoy.png"
            text: qsTr("我喜欢的音乐")
            MouseArea {
                id: playArea
                anchors.fill: parent
                onClicked:  {
                    //显示我喜欢的音乐
                }
            }
        }
    }


}
