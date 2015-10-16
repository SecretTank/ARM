import QtQuick 2.0
import QtMultimedia 5.0

Item{
    id: container
    property alias myOpacity : container.opacity
    property alias iSource: myButton.source
    property alias iSource2:myButton2.source
    property alias mynum: fw.height
    signal buttonClicked
    Rectangle{
        id:fw
        Image{
            MouseArea {
                anchors.fill: parent
                onPressed:   {container.buttonClicked();animateClick.start()}
                onClicked: { playSound.play()}
                onReleased:PropertyAnimation { target: myButton; property: "opacity";
                    to: 1 ;duration: 50; easing.type: Easing.OutSine  }
            }

            PropertyAnimation { id: animateClick;target: myButton; property: "opacity";
                                to: 0 ;duration: 50; easing.type: Easing.OutSine  }
            property real angle : 0
            property real distance : 0
            id:myButton
            height:miheight/12
            width:miheight/12
            z:1
        }
        Image{
            property real angle : 0
            property real distance : 0
            id:myButton2
            height:miheight/12
            width:miheight/12
            z:0
        }

    }
    SoundEffect {
           id: playSound
           source: "mybutton.wav"
       }
}

/*NumberAnimation {
        id: animateOpacity
        target: fw
        properties: "opacity"
        from: 1.0
        to: 0.80
        loops: Animation.Infinite
        easing {type: Easing.OutBack; overshoot: 500}
    }

}*/
