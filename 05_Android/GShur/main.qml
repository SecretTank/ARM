import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 430
    minimumWidth: 800
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

        color:"#171717"
        id: pageOverlay
        anchors.fill: parent
        Cell{iSource: "dayere.png";iSource2:"dayere_roshan.png" ;x:parent.width*0.920;y:370/500*parent.height;z:1}
        Cell{iSource: "mosalas.png";iSource2:"mosalas_r.png";x:parent.width*0.848;y:308/500*parent.height;z:1}
        Cell{iSource: "moraba.png";iSource2: "moraba_roshan.png";x:parent.width*0.775;y:370/500*parent.height;z:1}
        Cell{iSource: "zarbdar.png";iSource2: "zarbdar_r.png";x:parent.width*0.848;y:432.5/500*parent.height;z:1}
        Joystick{x:0;y:parent.height*3.2/5;z:1}
        CamLCD{}
    }
}
