import QtQuick 2.7
import QtQuick.Controls 1.5
import QtMultimedia 5.6

Item {

Video {
	id: video
	objectName: "video"
	x: 0
	y: 0
	width: 1280
	height: 720
	source: 'file:///C:/test/car.mp4'
	autoPlay: true
	onStopped: play()

	Connections {
		target: car
		onCarChanged: {
			if (carStatus) video.stop();
			else video.pause();
		}
	}
}
}