import QtQuick 2.0
import QtMultimedia 5.8
//苏雪莲 菜单
Rectangle {

    //默认为在线音乐界面
    property int currentButton:1
    property int previousButton: 1


    /*
     *onlineMusicButton:1 在线音乐
     *findMusicButton:2 本地音乐
     *downloadButton:3  下载音乐
     *
     *enjoyMusicButton：11 喜欢的音乐
     */


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
            id: onlineMusicButton
            color: "#dba4ae"
            picSource: "qrc:/images/icon-net.png"
            text: qsTr("在线音乐")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //隐藏其他界面
                    change(1)

                   //设置button颜色
                    onlineMusicButton.color = "#dba4ae"
                     //显示在线音乐界面
                    onlineInterface.visible = true
                }
            }
        }

        MenuButton {
            y: 20
            id: findMusicButton
            picSource: "qrc:/images/icon-music.png"
            text: qsTr("本地音乐")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //更改之前的设置
                    change(2)

                    findMusicButton.color = "#dba4ae"
                    //显示我的音乐界面
                    localMusicInterface.visible = true
                    //更改当前按钮
                }
            }
        }
        MenuButton {
            y: 100
            id: downloadButton
            picSource: "qrc:/images/download.png"
            text: qsTr("下载的音乐")
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //更改之前的设置
                    change(3)

                    downloadButton.color = "#dba4ae"
                    //显示我的音乐界面
                    songlistInterface.visible = true
                    songlistInterface.init(downloadButton.text)
                }
            }
        }

        //占行
        Text {
                text: qsTr("  ")
                font.pixelSize: 16
            }
        Text {
            id:label
//            anchors.top: downloadButton.bottom
//            anchors.topMargin: 30

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
                    //更改之前的设置
                    change(11)

                    enjoyMusicButton.color = "#dba4ae"
                    //显示我喜欢的音乐
                    songlistInterface.visible = true
                    songlistInterface.init(enjoyMusicButton.text)
                }
            }
        }
    }

    function change(index){
        previousButton = currentButton
        currentButton = index
        if(currentButton === previousButton){
            return
        }

        if(previousButton === 1 ){
            onlineMusicButton.color = "pink"
            onlineInterface.visible = false
            lyricInterface.visible = false
        }
        if(previousButton === 2 ){
            findMusicButton.color = "pink"
            localMusicInterface.visible = false
            lyricInterface.visible = false
        }
        if(previousButton === 3 ){
            downloadButton.color = "pink"
            //隐藏下载页面
            songlistInterface.visible = false
            lyricInterface.visible = false
        }
        if(previousButton === 11 ){
            enjoyMusicButton.color = "pink"
            //隐藏歌单界面
            songlistInterface.visible = false
            lyricInterface.visible = false
        }
    }

}
