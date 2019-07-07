import QtQuick 2.0
//苏雪莲
Item {
    Column{
        width: parent.width
        height: parent.height
        Row{
            width: parent.width
            height: parent.height/2
            SonglistItem{
                id:songlist1
                x:parent.width/12
                picSource: "qrc:/images/1.jpg"
                name: "华语"
            }
            SonglistItem{
                id:songlist2
                x:parent.width*5/12
                picSource: "qrc:/images/2.jpg"
                name: "英语"
            }
            SonglistItem{
                id:songlist3
                x:parent.width*9/12
                picSource: "qrc:/images/3.jpg"
                name: "日语"
            }

        }
        Row{
            width: parent.width
            height: parent.height/2
            SonglistItem{
                id:songlist4
                x:parent.width/12
                picSource: "qrc:/images/4.jpg"
                name: "古风"
            }
            SonglistItem{
                id:songlist5
                x:parent.width*5/12
                picSource: "qrc:/images/5.jpg"
                name: "摇滚"
            }
            SonglistItem{
                id:songlist6
                x:parent.width*9/12
                 picSource: "qrc:/images/6.jpg"
                name: "电音"
            }
        }

    }


}
