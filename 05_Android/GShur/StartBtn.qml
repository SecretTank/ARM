import QtQuick 2.0
import QtMultimedia 5.0

Item{
    id: container
    property alias myOpacity : container.opacity
    property bool isStarted: false

    property alias mynum: fw.height
    signal buttonClicked



    Rectangle{
        id:fw
        Image{
            MouseArea {
                anchors.fill: parent
                onPressed:   {container.buttonClicked()}
                onClicked: { playSound.play()}
                onReleased: {
                    if (container.isStarted)
                    {
                        animateOff.start()
                        container.isStarted = false
                    }
                    else
                    {
                        animateOn.start()
                        container.isStarted = true
                    }
                }
            }

            PropertyAnimation { id: animateOn;target: myButton; property: "opacity";
                                to: 0 ;duration: 50; easing.type: Easing.OutSine  }
            PropertyAnimation { id: animateOff;target: myButton; property: "opacity";
                                to: 100 ;duration: 50; easing.type: Easing.OutSine  }
            property real angle : 0
            property real distance : 0
            id:myButton
            source : "qrc:/Resources/powerBtnOff.png"
            height:miheight/8
            width:miheight/8
            z:1
        }
        Image{
            property real angle : 0
            property real distance : 0
            id:myButton2
            source : "qrc:/Resources/powerBtnOn.png"
            height:miheight/8
            width:miheight/8
            z:0
        }
    }
    SoundEffect {
           id: playSound
           source: "mybutton.wav"
       }
}

