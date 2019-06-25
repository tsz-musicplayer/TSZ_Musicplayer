import QtQuick 2.0

Item {
    id:songlistPart
    Rectangle {
        id:head
        width: parent.width
        height: 60
        color: "#fcfcfc"

        Text {
            id: songlistName
            x: 8
            y: 9
            text: qsTr("未知歌单")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 31
        }
    }

    Rectangle{//音乐列表
        width: parent.width
        height:songlistPart.height - playBar.height
        anchors.top:head.bottom

        MusicList{
            //anchors.top: localMusic.bottom
            width: parent.width
            height: parent.height
            visible: true
        }
    }

    function init(name){
        songlistName.text = name
        //获取名为"name"的歌单
    }

}
