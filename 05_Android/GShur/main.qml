import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id:page
    visible: true
    property alias miheight:page.width
    Rectangle{
        Rectangle {
            visible:false
            id:my
             width: 130
             height: 130
             x: 1360
             y:625
             color: "#095e7b"
             border.color: "#0a2f4a"
             border.width: 2
             radius: width*0.5
        }

        id: pageOverlay
        anchors.fill: parent
        Cell{iSource: "dayere.png";iSource2:"dayere_roshan.png" ;x:parent.width*0.915;y:370/500*parent.height}
        Cell{iSource: "mosalas.png";iSource2:"mosalas_r.png";x:parent.width*0.850;y:305/500*parent.height}
        Cell{iSource: "moraba.png";iSource2: "moraba_roshan.png";x:parent.width*0.780;y:370/500*parent.height}
        Cell{iSource: "zarbdar.png";iSource2: "zarbdar_r.png";x:parent.width*0.850;y:432.5/500*parent.height}
        Joystick{x:0;y:parent.height*3.2/5}
    }



}
