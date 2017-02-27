import QtQuick 2.7
import QtQuick.Controls 1.5
import QtMultimedia 5.6
import QtWebSockets 1.0

Item {

	Rectangle {
		color: "black"
		anchors.fill: parent
	}

	Video {
		id: video
		objectName: "video"
		anchors.fill: parent
		source: 'http://localhost:8888/run_stopfront.mp4'
		autoPlay: true
		onStopped: play()
		fillMode: VideoOutput.PreserveAspectCrop 

		Connections {
			target: wSocket
			onCarChanged: {
				if(carStatus == 'stop')
				{
					video.source = 'http://localhost:8888/run_stopfront.mp4';
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'crossroad'}");
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'acclda'}");
				}
				else if ( carStatus == 'run_crossroad')
				{
					video.source = 'http://localhost:8888/run_right.mp4';
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'camera'}");
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'opendoor'}");
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'acclda'}");
				}
				else if ( carStatus == 'run_frontcar')
				{
					video.source = 'http://localhost:8888/run_frontcareful.mp4';
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'camera'}");
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'opendoor'}");
					wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'crossroad'}");
				}
			}
			onHudLockChanged: {
				if (hudStatus == false )
				{
					speed.visible = true;
					speedText.visible = true;
				}
				else{
					speed.visible = false;
					speedText.visible = false;
				}
			}
		}

		onPositionChanged: {
			if (video.source == 'http://localhost:8888/run_frontcareful.mp4' && parseInt(position/1000) == 18)
			{
				wSocket.sendMessageFromQml("{'action': 'modeon', 'mode': 'acclda'}");
			}
			else if (video.source == 'http://localhost:8888/run_frontcareful.mp4' && parseInt(position/1000) == 21)
			{
				wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'acclda'}");
			}
			else if (video.source == 'http://localhost:8888/run_right.mp4' && parseInt(position/1000) == 6)
			{
				wSocket.sendMessageFromQml("{'action': 'modeon', 'mode': 'crossroad'}");
			}
			else if (video.source == 'http://localhost:8888/run_right.mp4' && parseInt(position/1000) == 16)
			{
				wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'crossroad'}");
			}
		}


	}

	Rectangle {
        id: rect
        width: 579
        height: 220
        color: "black"
        opacity: 0.4
        x: 373
        y: 469
    }

	Image {
		id: speed
		source: "qrc:///speed.png"
		x: 510
		y: 524
	}

	Text {
		id: speedText
		text: '60'
		x: 561
		y: 563
		font.pixelSize: 26
		font.weight: Font.Medium
		color: "lightsteelblue"
	}

	// Connections {
	// 	target: car
	// 	onCarChanged: {
	// 		if (carStatus) video.stop();
	// 		else video.pause();
	// 	}
	// }

	Loader {
		id: crossroad
		objectName: "crossroad"
	}
	Loader {
		id: opendoor
		objectName: "opendoor"
	}
	Loader {
		id: acclda
		objectName: "acclda"
	}

//	WebSocket {
//		id: socket
//		url: "ws://localhost:8888/map/pos"
//		active: true
//		onTextMessageReceived: {
//			var carData = eval("(" + message + ")");
//			if (carData['cross'] != "" && crossroad.opacity == 0) {
//				wSocket.sendMessageFromQml("{'action': 'modeon', 'mode': -1}");
//			}
//		}
//	}
	
}