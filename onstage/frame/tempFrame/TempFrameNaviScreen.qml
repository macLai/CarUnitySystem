import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Rectangle {
		color: "black"
		anchors.fill: parent
	}
	
	Loader {
		id: audio
		objectName: "audio"
		property var isPhoneOn: false

		Connections {
			target: wSocket
			onPhoneChanged: {
				audio.isPhoneOn = phoneStatus;
			}
		}
	}
	Loader {
		id: phone
		objectName: "phone"
	}

	Loader {
		id: crossroad
		objectName: "crossroad"
	}

	Loader {
		id: driverinfo
		objectName: "driverinfo"
	}

	Loader {
		id: energymonitor
		objectName: "energymonitor"
	}

	Loader {
		id: opendoor
		objectName: "opendoor"
	}

	Loader {
		id: camera
		objectName: "camera"
	}

	Loader {
		id: navi
		objectName: "navi"
	}

	Rectangle {
        id: rect
        width: 28
        height: 28
        color: "white"
        radius: 2
        opacity: navi.opacity
        x: navi.x + navi.width-width-10
        y: navi.y + 10

        Image {
        	id: moveIcon
        	x: 6
        	y: 6
    		source: "qrc:///move-option-16.png"
        }

        MouseArea {
        	id: mouseArea
            anchors.fill: parent
            drag.target: rect
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: window.width - rect.width
            drag.minimumY: 0
            drag.maximumY: window.height - rect.height

            property var moved: false

            onPositionChanged: {
            	if(pressed == true) {
            		moved = true;
            	}
            }
            onReleased: {
            	if(moved == true) {
            		if(moveArea.x==0 && moveArea.y==0 && moveArea.width==window.width)
						wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': 0}");
					else if(moveArea.x==0 && moveArea.y==0 && moveArea.width==window.width/2)
						wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': 1}");
					else if(moveArea.x==window.width/2 && moveArea.y==0 && moveArea.width==window.width/2 && moveArea.height==window.height)
						wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': 2}");
					else if(moveArea.x==window.width/2 && moveArea.y==0 && moveArea.width==window.width/2 && moveArea.height==window.height/2)
						wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': 3}");
					else if(moveArea.x==window.width/2 && moveArea.y==window.height/2 && moveArea.width==window.width/2 && moveArea.height==window.height/2)
						wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': 4}");
        		}
        		else {
        			wSocket.sendMessageFromQml("{'action': 'lockmap', 'pos': -1}");
        		}
        		rect.x = Qt.binding(function() {return navi.x+navi.width-rect.width-10;});
        		rect.y = Qt.binding(function() {return navi.y+10;});
        		moved = false;
            }
        }
    }

    Connections {
		target: wSocket
		onLockChanged: {
			if (lockStatus) moveIcon.source = "qrc:///pin-16.png";
			else moveIcon.source = "qrc:///move-option-16.png";
		}
	}

	Rectangle {
		id: moveArea
		color: "white"
		opacity: 0.25
		visible: mouseArea.drag.active
		x: {
			if( rect.x < window.width/2) return 0;
			else return window.width/2;
		}
		y: {
			if(x == 0) return 0;
			if(rect.y < window.height/2) return 0;
			if(rect.x < window.width/4*3 && rect.y < window.height/3*2) return 0;
			else return window.height/2;
		}
		width: {
			if(x != 0 || y != 0) return window.width/2;
			if(rect.x < window.width/4 || rect.y < window.height/3 || rect.y >window.height/3*2) return window.width/2;
			return window.width;
		}
		height: {
			if(x == 0 && y == 0) return window.height;
			if(y != 0) return window.height/2;
			if(rect.y < window.height/3) return window.height/2;
			if(rect.x > window.width/4*3 && rect.y < window.height/2) return window.height/2;
			else return window.height;
		}
	}

}