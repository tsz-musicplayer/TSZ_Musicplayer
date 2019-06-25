import QtQuick 2.7
import QtQuick.Layouts 1.3

//周敏 显示音乐列表详细
Item {
    id: listBar
    width: parent.width
    height: 30
    anchors.top:parent.top


    property string listBar1 : "test"
    property string listBar2 : "test"
    property string listBar3 : "test"
    property string listBar4 : "test"
    property string listBar5 : "test"
    property string listBar6 : "null"
    //property string source

    property bool title: false
    property bool coloring : false

    property int borderWidth : title ? 1 : 0
    property color borderColor :  title ? "grey" :"white"
    property color highlightColor: "#dba4ae"

    property color musicBarColor : coloring ? "pink" : "white"

//    MouseArea{
//        anchors.fill: parent
//        onClicked:{
//            listBar.ListView.view.currentIndex = index
//            console.log(index)
//        }
//        onDoubleClicked: listBar.ListView.view.model.remove(index)
//    }



    Rectangle{
        id:bar1
        width: listBar.width / 6
        height: listBar.height
        anchors.left: listBar.left
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth

        Text{
            id: bar1txt
            text: listBar1
            horizontalAlignment: Text.AlignHCenter
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

    Rectangle{
        id:bar2
        width:listBar.width / 6
        height: listBar.height
        anchors.left: bar1.right
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth
        Text{
            id: bar2text
            text: listBar2
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

    Rectangle{
        id:bar3
        width:listBar.width / 6
        height: listBar.height
        anchors.left: bar2.right
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth
        Text{
            id: bar3txt
            text: listBar3
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

    Rectangle{
        id:bar4
        width:listBar.width / 6
        height: listBar.height
        anchors.left: bar3.right
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth
        Text{
            id: bar4txt
            text: listBar4
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

    Rectangle{
        id:bar5
        width:listBar.width / 6
        height: listBar.height
        anchors.left: bar4.right
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth
        Text{
            id: bar5txt
            text: listBar5
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

    Rectangle{
        id:bar6
        width:listBar.width / 6
        height: listBar.height
        anchors.left: bar5.right
        color: musicBarColor
        border.color: borderColor
        border.width: borderWidth
        Text{
            id: bar6txt
            text: listBar6
            padding: (listBar.height - bar1txt.contentHeight) / 2
        }
    }

}
