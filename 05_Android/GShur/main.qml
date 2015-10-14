import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    Rectangle{
        Rectangle {
            visible:false
            id:my
             width: 120
             height: 120
             x: 1080
             y:540
             color: "#095e7b"
             border.color: "#0a2f4a"
             border.width: 2
             radius: width*0.5
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
