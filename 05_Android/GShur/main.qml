import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 430
    minimumWidth: 800
    //Properties:
    property string ipAddress: "172.16.34.204"

    //Signals:
    signal morabaSignal
    signal mosalasSignal
    signal dayereSignal
    signal zarbdarSignal
    signal startSignal(string IP)
    Dialog{
        id: setting_dialog
        visible: false

        //width: page.width * 0.4
        //height : page.height * 0.2
        contentItem: Rectangle{
            id:setting_container
            color: "#262626"
            width:page.width*0.5
            height:page.height*0.35
            ColumnLayout
            {
                id : setting_layout
                anchors.centerIn : parent

                RowLayout{
                    id : ip_layout
                    Label
                    {
                        text : "IP Address"
                        color: "#f3f4f3";
                        Layout.leftMargin: page.height * 0.05
                    }

                    TextField{
                        id : ip_textfield
                        placeholderText: ipAddress
                    }
                }
                Button
                {
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: page.height * 0.01
                    Layout.bottomMargin: page.height * 0.02
                    onClicked: {page.ipAddress = ip_textfield.text ; setting_dialog.close()}
                    style: ButtonStyle{
                            background: Rectangle{ implicitWidth: 75; implicitHeight:25;
                                color: "#5b595c"}
                            //label : Text{color: "#f3f4f3"}
                                    //text:"is It"}
                            label : Text{
                                color: "#f3f4f3";
                                text:"Ok";
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                }
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
                     text: "#1026"
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
        StartBtn{x:parent.width*0.6;y:370/500*parent.height;z:1 ;onButtonClicked:page.startSignal(page.ipAddress)}
        Joystick{x:30;y:parent.height*2.8/5;z:1; }
        CamLCD{}
    }
}
