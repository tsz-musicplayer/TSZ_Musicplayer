import QtQuick 2.0

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
                name: "a"
            }
            SonglistItem{
                id:songlist2
                x:parent.width*5/12
                picSource: "qrc:/images/2.jpg"
                name: "b"
            }
            SonglistItem{
                id:songlist3
                x:parent.width*9/12
                picSource: "qrc:/images/3.jpg"
                name: "c"
            }

        }
        Row{
            width: parent.width
            height: parent.height/2
            SonglistItem{
                id:songlist4
                x:parent.width/12
                picSource: "qrc:/images/4.jpg"
                name: "d"
            }
            SonglistItem{
                id:songlist5
                x:parent.width*5/12
                picSource: "qrc:/images/5.jpg"
                name: "e"
            }
            SonglistItem{
                id:songlist6
                x:parent.width*9/12
                picSource: "qrc:/images/6.jpg"
                name: "f"
            }
        }

    }


}
