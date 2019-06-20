import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
//import PlayMusic 1.0

import "./qml"
Window {
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

    LocalMusicInterface {
        id: localMusicInterface
        anchors.bottom: playBar.top
        anchors.top: topBar.bottom
        anchors.left: content.right
        width: window.width - content.width
        height: window.height - topBar.height - playBar.height
        anchors.bottomMargin: 0
        anchors.topMargin: 0
    }


}
