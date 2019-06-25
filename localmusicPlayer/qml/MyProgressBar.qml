import QtQuick 2.0
import QtQuick.Controls 1.2

//苏雪莲
//播放进度条

Slider{
    width: 400
    id:slider
    x: -65
    y: 25
    value: proportion
    MouseArea{
        anchors.rightMargin: 65
        anchors.bottomMargin: 8
        anchors.leftMargin: -65
        anchors.topMargin: -8
        anchors.fill:parent
        onClicked: {
            proportion = (mouse.x-65) /width

            console.log("myPlayer.duration:", myPlayer.duration)
            //更新播放器的进度
            myPlayer.setPosition(proportion*myPlayer.duration)
            timer.start()
            //setValue()
        }
    }

    function setValue(){

        value = myPlayer.position/myPlayer.duration

    }

}

