import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
//import PlayMusic 1.0

import "./qml"
Window {
    property int currentIndex
    property double proportion: myPlayer.position/myPlayer.duration
    id: window
    height: 640
    width: 1024
    visible: true
    title: qsTr("Music Player")

    property string playMusicSource

    //    PlayMusic {
    //        id: myPlayer

    //    }

    TopBar {
        id: topBar
        //width: 1024
        width: window.width
        height: 60

    }

    PlayBar {
        id: playBar
        x: 0
        y: 580
        //width: 1024
        width: window.width
        height: 60
        anchors.bottomMargin: parent.y
    }

    Content {
        id: content
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        width: 200
        //width: window.width / 5
    }

    //本地音乐界面
    LocalMusicInterface {
        id: localMusicInterface
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        anchors.left: content.right
        width: window.width - content.width
        height: window.height - topBar.height - playBar.height
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        visible: false
    }

    //歌词界面
    LyricInterface{
        id: lyricInterface
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        anchors.left: content.right
        width: window.width - content.width
        height: window.height - topBar.height - playBar.height
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        visible: false
    }

    //在线推荐歌单界面
    OnlineInterface{
        id: onlineInterface
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        anchors.topMargin: 10
        anchors.left: content.right
        width: window.width - content.width
        height: window.height - topBar.height - playBar.height
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
    }

    //歌单界面
    SonglistInterface{
        id:songlistInterface
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        anchors.left: content.right
        width: window.width - content.width
        height: window.height - topBar.height - playBar.height
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        visible: false
    }

    Timer {
        id:timer
           //定时器触发执行onTriggered()信号处理函数，可以定义一些操作
           interval: 500    //interval属性用来设置时间间隔，单位是毫秒，默认值是1000毫秒；
           running:true         //running属性为true时开启定时器，否则停止定时器
           repeat:true  //repeat属性设置是否重复触发，如果为false，值触发一次，并将running自动设为false
           onTriggered: proportion = myPlayer.position/myPlayer.duration
       }

}
