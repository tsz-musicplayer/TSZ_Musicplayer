import QtQuick 2.0
import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtMultimedia 5.8
//苏雪莲
Rectangle {
    id: root
    width: 1000
    height: 60
    color: "pink"

    property int iconSize: 20

    property bool bPlaying: false
    property int nPlayIndex: 0

    // 歌曲名字
    Rectangle {
        id: musicNameRect
        color: "transparent"
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 150
        Text {
            id: musicName
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            text: qsTr("未知歌曲")
            font.pointSize: 10
            font.bold: true
            elide: Text.ElideRight
        }
    }

    // 进度条
    MyProgressBar {
        id: progressBar
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 25
    }

    // 播放、暂停按钮
    Rectangle {
        id: playButton
        //anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.top: parent.top
        width: 40
        height: 40
        color: "transparent"
        Image {
            id: playImg
            source: bPlaying === true ? "qrc:/images/stop.png" : "qrc:/images/play.png"
            width: 40
            height: 40
        }
        MouseArea {
            id: last
            anchors.leftMargin: -5
            anchors.topMargin: -7
            anchors.fill: parent
            onPressed: {
                if (bPlaying) {
                    playImg.source = "qrc:/images/play.png"
                } else {
                    playImg.source = "qrc:/images/stop.png"
                }
            }
            onReleased: {
                if (bPlaying) {
                    playImg.source = "qrc:/images/play.png"
                } else {
                    playImg.source = "qrc:/images/stop.png"
                }
            }
            onClicked: {
                if (bPlaying) {
                    console.log("pause : " + bPlaying)
                    //   CppLocalMusic.pauseMusic()
                    bPlaying = false
                    playImg.source = "qrc:/images/play.png"
                    myPlayer.pause()
                } else {
                    console.log("重新播放")

                    bPlaying = true
                    playImg.source = "qrc:/images/stop.png"
                    myPlayer.play(playMusicSource)
                }

               // myPlayer.playOnline("rtsp://192.168.43.194/zm.mp3")
            }
        }
    }
    // 上一首按钮
    Rectangle {
        id: lastButton
        anchors.rightMargin: 10
        anchors.right: playButton.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "transparent"
        width: 32
        height: 32
        Image {
            id: lastImg
            source: "qrc:/images/last.png"
            width: 32
            height: 32
        }
        MouseArea {
            id: lastSong
            anchors.fill: parent

            onPressed: {
                lastImg.visible = false
            }
            onReleased: {
                lastImg.visible = true
            }

            onClicked: {

                //播放当前播放列表的上一首
                currentIndex = (currentIndex-1 + myPlayListModel.musicCount()) % myPlayListModel.musicCount()
                myPlayer.play(myPlayListModel.getMusicSource(currentIndex))
                console.log("currentIndex:  ",currentIndex)
                console.log("myPlayListModel.musicCount():  ",myPlayListModel.musicCount())
                setMusicName(myPlayListModel.getMusicName(currentIndex))

            }
        }
    }
    // 下一首按钮
    Rectangle {
        id: nextButton
        anchors.rightMargin: 10
        anchors.left: playButton.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "transparent"
        width: 32
        height: 32
        Image {
            id: nextImg
            source: "qrc:/images/next.png"
            width: 32
            height: 32
        }
        MouseArea {
            id: nextSong
            anchors.fill: parent
            onPressed: {
                nextImg.visible = false
            }
            onReleased: {
                nextImg.visible = true
            }
            onClicked: {
                //播放当前播放列表的下一首
                currentIndex = (currentIndex+1 + myPlayListModel.musicCount()) % myPlayListModel.musicCount()
                myPlayer.play(myPlayListModel.getMusicSource(currentIndex))
                setMusicName(myPlayListModel.getMusicName(currentIndex))
            }
        }
    }
    // 喜欢收藏音乐按钮
    Rectangle {
        id: enjoyRect
        width: iconSize
        height: iconSize
        anchors.right:lyricRect.left
        anchors.rightMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"
        Image {
            id: enjoyImg
            source: "qrc:/images/icon-enjoy.png"
            width: iconSize
            height: iconSize
        }
        MouseArea {
            id: enjoySong
            anchors.fill: parent
            onPressed: {
                enjoyImg.visible = false
            }
            onReleased: {
                enjoyImg.visible = true
            }
            onClicked: {

                //将音乐添加到歌单-我喜爱的音乐

                //播放流媒体音乐
                myPlayer.playOnline("rtsp://192.168.31.10/tf.mp3")
            }
        }
    }

    //歌词
    Rectangle {
        id: lyricRect
        width: iconSize
        height: iconSize
        anchors.right:parent.right
        anchors.rightMargin: 60
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"
        Image {
            id: lyricImg
            source: "qrc:/images/lyric.png"
            width: iconSize
            height: iconSize
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                lyricImg.visible = false
            }
            onReleased: {
                lyricImg.visible = true
            }
            onClicked: {
                //显示歌词界面
                lyricInterface.visible = true
                console.log("歌词的显示")

                //隐藏其他界面
                localMusicInterface.visible = false
                onlineInterface.visible = false
                songlistInterface.visible = false

            }
        }
    }


    //设置音乐名称
    function setMusicName(name){
        musicName.text = name
    }
    function seekPostion(){
        progressBar.value = myPlayer.position/myPlayer.duration
    }
}
