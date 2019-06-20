import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3


//周敏 音乐列表
Item{
    id:musicListPage
    anchors.top:parent.top
    anchors.bottom: parent.bottom
    width: localMusicPage.width
    height:parent.height

    MusicListBar{ //标题
        id:musicListBarTitle
        anchors.top:parent.top
        width: musicListPage.width
        title: true
        borderWidth: 1
        borderColor: "grey"

        listBar1: "序号 "
        listBar2: "音乐标题"
        listBar3: "歌手"
        listBar4: "专辑"
        listBar5: "时长"
        listBar6: "大小"
    }

    Rectangle{//歌曲列表
        width: musicListPage.width
        height: musicListPage.height - musicListBarTitle.height
        anchors.top: musicListBarTitle.bottom
        ListView {
            id: musicList
            width:parent.width
            height:parent.height
            x: 30
            focus: true
            //clip: true
            //orientation: ListView.Vertical //垂直方向
            //        snapMode: ListView.SnapToItem //
            //        cacheBuffer: 2
            anchors.fill: parent
            anchors.top: musicListBarTitle.bottom
            visible: true

            model: myPlayListModel
            delegate: detail
        }

//        ListModel{
//            id:musicModel
//            ListElement{name: "a1"; singer:"b"; album: "c"; time:"d"; size:"e"}
//            ListElement{name: "a2"; singer:"b"; album: "c"; time:"d"; size:"e"}
//            ListElement{name: "a3"; singer:"b"; album: "c"; time:"d"; size:"e"}
//        }

    }
    Component{//委托显示音乐信息
        id: detail
        Rectangle{
            width: musicList.width
            height: musicListBarTitle.height
            y: musicListBarTitle.y + musicListBarTitle.height
            //anchors.top: musicListBarTitle.bottom
            MusicListBar{
                id:musicBar
                // anchors.top: musicListPage.top
                //anchors.top: musicListBarTitle.bottom
                width: musicListPage.width
                listBar1: " " + index
                listBar2: " " + name
                listBar3: " " + singer
                listBar4: " " + album
//                listBar5: " " + time
//                listBar6: " " + size

                coloring: index % 2 ? false : true
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    console.log(index, source)

                   // playMusicSource = myPlayListModel.next(index)
                    playMusicSource = source
                    myPlayer.play(playMusicSource)
                    playBar.setMusicName(name)
                    console.log("----------------")
                    console.log(myPlayer.duration)


                    //                    wrapper.ListView.view.currentIndex = index
                    //                        onDoubleClicked: wrapper.ListView.view.model.remove(index)
                }
            }
        }
    }
}



