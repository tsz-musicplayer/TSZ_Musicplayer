import QtQuick 2.0

//苏雪莲 自定义歌单组件
Item {
    property alias picSource: songlistPic.source
    property alias name: songlistname.text

    id:songlist
    Image {
        id:songlistPic
        width: 150
        height: 200
    }
    Text{
        width: songlistPic.width
        anchors.top: songlistPic.bottom
        anchors.topMargin: 5
        id:songlistname
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideNone
    }

}
