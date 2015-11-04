import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 430
    minimumWidth: 800
    signal morabaSignal
    signal mosalasSignal
    signal dayereSignal
    signal zarbdarSignal
    Dialog{
        id: setting_dialog
        visible: true
        //width: page.width * 0.4
        //height : page.height * 0.2
        contentItem: ColumnLayout
        {
            id : setting_layout
            anchors.centerIn : parent
            RowLayout{
                id : ip_layout
                Label
                {
                    text : "IP Address"
                    Layout.leftMargin: page.height * 0.05
                }

                TextField{
                    placeholderText: "172.16.156.204"
                }
            }
            Button
            {
                text : "Ok"
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: page.height * 0.05
                Layout.bottomMargin: page.height * 0.02
                onClicked: setting_dialog.close()
            }
        }

    }

    Rectangle{
        Rectangle {
            visible:true
            id:my
             x: 10
             y:0
             Text {
                     id: helloText
                     text: "#0056"
                     y: 10
                     anchors.horizontalCenter: page.horizontalCenter
                     font.pointSize: 20; font.bold: true
                     color:"#ffffff"
             }
        }

       Image
        {
            z:2
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: page.width * 0.01
            anchors.rightMargin: page.width * 0.01
            source: "qrc:/Resources/settings.png"
            id:setting_image
            width : page.width * 0.06
            height: setting_image.width
            MouseArea
            {
                id:setting_mousearea
                anchors.fill: parent
                onClicked: {console.log("Hello Boys!"),setting_dialog.open()}
            }
        }

        color:"#171717"
        id: pageOverlay
        anchors.fill: parent
        Cell{iSource: "dayere.png";iSource2:"dayere_roshan.png" ;x:parent.width*0.920;y:370/500*parent.height;z:1
            ;onButtonClicked:page.dayereSignal()}
        Cell{iSource: "mosalas.png";iSource2:"mosalas_r.png";x:parent.width*0.848;y:308/500*parent.height;z:1
            ;onButtonClicked:page.mosalasSignal()}
        Cell{iSource: "moraba.png";iSource2: "moraba_roshan.png";x:parent.width*0.775;y:370/500*parent.height;z:1
            ;onButtonClicked:page.morabaSignal()}
        Cell{iSource: "zarbdar.png";iSource2: "zarbdar_r.png";x:parent.width*0.848;y:432.5/500*parent.height;z:1
            ;onButtonClicked:page.zarbdarSignal()}
        Joystick{x:0;y:parent.height*3.2/5;z:1}
        CamLCD{}
    }
}
