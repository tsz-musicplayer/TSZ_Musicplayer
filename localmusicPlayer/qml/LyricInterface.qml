import QtQuick 2.0

Item {

    Text{
        x: 440
        y: 232
        text:"暂无歌词"
        font.pointSize: 18
    }

    Image {
        id: image
        x: 49
        y: 113
        width: 204
        height: 196
        source: "qrc:/images/bg.jpg"
    }
    
    Rectangle {
        id: rectangle
        x: 297
        y: 13
        width: 343
        height: 69
        color: "#ffffff"
        Text{
            id:name
            x: 8
            y: 8
            width: 69
            height: 28
            text:"未知歌曲"
            font.pointSize: 20
        }
        Row{
            id:albumRow
            x: 14
            y: 42
            width: 140
            height: 27
            Text{
                id:albumLable
                text:"专辑："
                font.pointSize: 16
            }
            Text{
                id:albumText
                text:"未知专辑"
                font.pointSize: 16
            }
        }
        Row{
            id:singerRow
            x: 195
            y: 42
            width: 140
            height: 27
            Text{
                id:singerLable
                text:"歌手："
                font.pointSize: 16
            }
            Text{
                id:singerText
                text:"未知歌手"
                font.pointSize: 16
            }
        }
    }

//    function set(){
//        name.text = myPlayListModel.getMusicName(currentIndex)
//        albumText.text = myPlayListModel.getMusiAlbum(currentIndex)
//        singerText.text =myPlayListModel.getMusicSinger(currentIndex)
//    }
}
