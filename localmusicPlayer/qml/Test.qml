import QtQuick 2.0

Rectangle {
    id:test
    width: parent.width;
    height: parent.height

    // Define a delegate component.  A component will be
    // instantiated for each visible item in the list.
    Component {
        id: petDelegate
        Item {
            id: wrapper
            width: test.width
            height: 30
            MusicListBar{
                id:musicBar
//                anchors.top: musicListBarTitle.bottom
//                width: musicListPage.width
                width: parent.width
                listBar1: " " + index
                listBar2: " " + name
                listBar3: " " + singer
                listBar4: " " + album
                listBar5: " " + time
                listBar6: " " + size
                coloring: index % 2 ? false : true
            }

            // indent the item if it is the current item
//            states: State {
//                name: "Current"
//                when: wrapper.ListView.isCurrentItem
//                PropertyChanges { target: wrapper; x: 20 }
//            }
//            transitions: Transition {
//                NumberAnimation { properties: "x"; duration: 200 }
//            }
            MouseArea {
                anchors.fill: parent
                onClicked: wrapper.ListView.view.currentIndex = index
            }
        }
    }

    // Define a highlight with customized movement between items.
    Component {
        id: highlightBar
        Rectangle {
            width: test.width; height: 30
            color: "#FFFF88"
            y: listView.currentItem.y;
//            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }

    ListView {
        id: listView
        width: test.width
        height: parent.height
        x: 30

        model: musicModel
        delegate: petDelegate
        focus: true

        // Set the highlight delegate. Note we must also set highlightFollowsCurrentItem
        // to false so the highlight delegate can control how the highlight is moved.
        highlight: highlightBar
        highlightFollowsCurrentItem: false
    }

    ListModel{
        id:musicModel
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
        ListElement{name: "a"; singer:"b"; album: "c"; time:"d"; size:"e"}
    }
}
