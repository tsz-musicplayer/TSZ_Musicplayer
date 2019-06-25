import QtQuick 2.0
import QtQuick.Dialogs 1.2
//苏雪莲 本地音乐
Rectangle {
    id:localMusicPage
    color: "transparent"
    width: parent.width

    Rectangle {
        id: localMusic
        x: 0
        y: 0
        width: parent.width
        height: 60
        color: "#fcfcfc"

        Text {
            id: localTitle
            x: 8
            y: 9
            text: qsTr("本地音乐")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 31
        }

        Text {
            id: text1
            x: 160
            y: 28
            width: 73
            height: 33
            text: qsTr("选择目录")
            font.underline: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    fileDialog.visible = true
                }
            }
        }

        //音乐列表


        FileDialog {
            id: fileDialog
            title: "选择播放目录"
            folder: shortcuts.home
            selectFolder: true
            onAccepted: {

                myPlayer.setDocument(fileUrl)
                myPlayListModel = myPlayer.playlist
                console.log("You chose: " + fileDialog.fileUrl)

            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: visible = false
        }
    }

    Rectangle{//音乐列表
        width: parent.width
        height:localMusicPage.height - playBar.height
        anchors.top: localMusic.bottom

        MusicList{
            //anchors.top: localMusic.bottom
            width: parent.width
            height: parent.height
            visible: true
        }
    }

    //    Test{

    //    }

}
