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
	height: 768
	source: "car.mp4"
	autoPlay: true
}
}