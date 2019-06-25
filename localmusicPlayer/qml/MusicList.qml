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
            //anchors.top: musicListBarTitle.bottom
            visible: true
            currentIndex: currentIndex
            model: myPlayListModel
            delegate: detail

        }

    }
    Component{//委托显示音乐信息
        id: detail
        Rectangle{
            width: musicList.width
            height: musicListBarTitle.height
            y: musicListBarTitle.y + musicListBarTitle.height
            color: musicList.isCurrentItem?"#157efb":"#53d769" //选中颜色设置

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
                listBar5: " " + duration
                listBar6: " " + size

                coloring: index % 2 ? false : true
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    console.log(index, source)

                    playMusicSource = source
                    myPlayer.play(playMusicSource)
                    playBar.bPlaying = true
                    playBar.setMusicName(name)

                    console.log("myPlayer.duration:", myPlayer.duration)

                    //设置更改当前播放索引
                    currentIndex = index

                    //高亮当前歌曲


                }
            }
        }
    }

}



