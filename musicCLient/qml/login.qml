import QtQuick 2.0
import QtQuick.Controls 1.4
import Login 1.0


ApplicationWindow {
    visible: true
    width: 400
    height: 250
    color: "#ffffff"
    title: qsTr("QuickControlsDemo")

    Text {
        id: text1
        x: 0.25*parent.width
        y: 115
        width: 68
        height: 25
        text: qsTr("用户名：")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14
    }

    TextField {
        id: textField1
        x: 0.43*parent.width
        y: 115
        width: 172
        height: 25
        placeholderText: qsTr("请输入用户名")
    }

    Text {
        id: text2
        x: 0.25*parent.width
        y: 151
        width: 68
        height: 25
        text: qsTr("密  码：")
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14
        horizontalAlignment: Text.AlignRight
    }

    TextField {
        id: textField2
        x: 0.43*parent.width
        y: 155
        width: 172
        height: 25
        echoMode: 2
        placeholderText: qsTr("请输入密码")
    }

    Button {
        id: button1
        x: 0.23*parent.width
        y: 200
        width: 116
        height: 32
        text: qsTr("登 陆")
        onClicked:{
//            testUserModel.user_id=textField1.text
//            testUserModel.password=textField2.text
            login(textField1.text, textField2.text)

        }
    }

    Button {
        id: button2
        x: 0.63*parent.width
        y: 200
        width: 110
        height: 32
        text: qsTr("注 册")
        onClicked:
        {
            sign(textField1.text, textField2.text)
        }
    }

    Image {
        id: image
        x: 0.07*parent.width
        y: 120
        width: 56
        height: 56
        source: "qrc:/image/2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image1
        x: 0
        y: 0
        width: parent.width
        height: 100
        source: "qrc:/image/1.png"
        fillMode: Image.PreserveAspectFit
    }

    function login(account,password){
        //testUserModel.checkUserinfo(account,password)
        console.log(testUserModel.checkUserinfo(account,password))
    }
    function sign(account,password){
        console.log(testUserModel.saveUserinfo(account,password))
    }
}
