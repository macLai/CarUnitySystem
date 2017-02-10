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
		source: 'http://localhost:8888/run_stopfront.m4v'
		autoPlay: true
		onStopped: play()
		fillMode: VideoOutput.PreserveAspectCrop 
	}

	Image {
		source: "qrc:///speed.png"
		x: 510
		y: 419
	}

	Text {
		text: '60'
		x: 561
		y: 458
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

	WebSocket {
		id: socket
		url: "ws://localhost:8888/map/pos"
		active: true
		onTextMessageReceived: {
			var carData = eval("(" + message + ")");
			if (carData['cross'] != "" && crossroad.opacity == 0) {
				wSocket.sendMessageFromQml("{'action': 'modeon', 'mode': -1}");
			}
		}
	}
	
}