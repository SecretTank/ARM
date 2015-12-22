import QtQuick 2.1
Item{
    id:container
    signal touchUpdated(int xx,int yy)
    signal sendKey(string key)
    signal sendNone
    Rectangle {
        id: joysticks
        Image {
            id: joystick

            property real angle : 0
            property real distance : 0

            source: "back.png"
            smooth: true
            width: miheight*0.2
            height:  miheight*0.2
            //anchors.centerIn: parent

            ParallelAnimation {
                id: returnAnimation
                NumberAnimation { target: thumb.anchors; property: "horizontalCenterOffset";
                    to: 0; duration: 100; easing.type: Easing.OutSine }
                NumberAnimation { target: thumb.anchors; property: "verticalCenterOffset";
                    to: 0; duration: 100; easing.type: Easing.OutSine }
            }
                MultiPointTouchArea {
                    id:mouse
                    anchors.fill: parent
                    touchPoints: [
                        TouchPoint { id: point1 }
                    ]
                property real fingerAngle : Math.atan2(point1.x, point1.y)
                property int mcx : point1.x - width * 0.5
                property int mcy : point1.y - height * 0.5
                property real mouse_x: point1.y-width*0.5-container.x
                property real mouse_y: point1.x+joystick.height-container.y
                property real xx:point1.x
                property real yy: point1.y
                property bool fingerOutOfBounds : fingerDistance2 < distanceBound2
                property real fingerDistance2 : mcx * mcx + mcy * mcy
                property real distanceBound : width * 0.5 - thumb.width * 0.4
                property real distanceBound2 : distanceBound * distanceBound
                onPressed: {
                    returnAnimation.stop()
                }
                onReleased: {
                     sendNone()
                    returnAnimation.restart()
                }
                onTouchUpdated: {
                    var angle2=Math.atan2(-thumb.anchors.verticalCenterOffset,thumb.anchors.horizontalCenterOffset)/3.14159265*180
                    //console.log(angle2)
                    if(fingerDistance2 > distanceBound2/4){
                    if(angle2>-45&&angle2<45){
                        //console.log("right")
                        sendKey("r")
                    }
                    else if(angle2>45&&angle2<135){
                        //console.log("up")
                        sendKey("u")
                    }
                    else if(angle2>135||angle2<-135){
                        //console.log("left")
                        sendKey("l")
                    }
                    else if(angle2<-45&&angle2>-135){
                        //console.log("down")
                        sendKey("d")
                    }

                    }
                    else{
                        console.log("none")
                        sendNone()
                    }
                    container.touchUpdated(xx,yy)
                    if (fingerOutOfBounds) {
                        thumb.anchors.horizontalCenterOffset = mcx
                        thumb.anchors.verticalCenterOffset = mcy
                    } else {
                        var angle = Math.atan2(mcy, mcx)
                        thumb.anchors.horizontalCenterOffset = Math.cos(angle) * distanceBound
                        thumb.anchors.verticalCenterOffset = Math.sin(angle) * distanceBound
                    }
                }
            }

            Image {
                id: thumb
                source: "cursuor.png"
                smooth: true
                height: joystick.height/2.5
                width: joystick.width/2.5
                anchors.centerIn: parent
            }

            Image {
                id: arrow
                source: "arrow.png"
                smooth: true
                z:1
                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -parent.height/1.75
            }
            Image {
                id: blow_arrow
                source: "blueArrow.png"
                smooth: true
                z:0
                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -parent.height/1.75
            }
            Image {
                id: blow_arrow_right
                source: "blueArrow.png"
                smooth: true
                z:0
                transform: Rotation{
                    angle:90
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset:-parent.height/10
                anchors.horizontalCenterOffset: parent.width/1.18
            }

            Image {
                id: arrow_right
                source: "arrow.png"
                smooth: true
                z:1
                transform: Rotation{
                    angle:90
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset:-parent.height/10
                anchors.horizontalCenterOffset: parent.width/1.18
            }
            Image {
                id: blow_arrow_left
                source: "blueArrow.png"
                smooth: true
                z:0
                transform: Rotation{
                    angle:-90
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset:parent.width/3.4+1
                anchors.horizontalCenterOffset: -parent.width/2.25
            }
            Image {
                id: arrow_left
                source: "arrow.png"
                smooth: true
                z:1
                transform: Rotation{
                    angle:-90
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
                anchors.verticalCenterOffset:parent.width/3.4+1
                anchors.horizontalCenterOffset: -parent.width/2.25
            }

            Image {
                id: blow_arrow_bot
                source: "blueArrow.png"
                smooth: true
                z:0
                transform: Rotation{
                    angle:180
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
               anchors.verticalCenterOffset:parent.width/1.3
                anchors.horizontalCenterOffset: parent.width/2.65
            }
            Image {
                id: arrow_bot
                source: "arrow.png"
                smooth: true
                z:1
                transform: Rotation{
                    angle:180
                }

                height: joystick.height/5
                width: joystick.width/2.5
                anchors.centerIn: parent
               anchors.verticalCenterOffset:parent.width/1.3
                anchors.horizontalCenterOffset: parent.width/2.65
            }


        }
    }
}

/*Rectangle{
    Rectangle {
        width: 1000; height: 1000
        color:"red"
        MultiPointTouchArea {
            anchors.fill: parent
            touchPoints: [
                TouchPoint { id: point1 }
            ]
            //onGestureStarted: console.log("hello")
            onPressed: console.log("meow")
            onReleased: console.log("bye")
        }

        Rectangle {
            width: 30; height: 30
            color: "green"
            x: point1.x
            y: point1.y
        }
    }*/

