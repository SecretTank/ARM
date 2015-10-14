import QtQuick 2.1
Item{
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
                    anchors.fill: parent
                    touchPoints: [
                        TouchPoint { id: point1 }
                    ]
                property real fingerAngle : Math.atan2(point1.x, point1.y)
                property int mcx : point1.x - width * 0.5
                property int mcy : point1.y - height * 0.5
                property bool fingerOutOfBounds : fingerDistance2 < distanceBound2
                property real fingerDistance2 : mcx * mcx + mcy * mcy
                property real distanceBound : width * 0.5 - thumb.width * 0.4
                property real distanceBound2 : distanceBound * distanceBound
                onPressed: returnAnimation.stop()
                onReleased: returnAnimation.restart()
                onGestureStarted: {
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

