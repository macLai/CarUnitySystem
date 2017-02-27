import QtQuick 2.7
import QtQuick.Controls 1.5
import QtWebView 1.1
import QtMultimedia 5.6

Item {
	Video {
		anchors.fill: parent
		source: 'http://localhost:8888/run_backcamera.mp4'
		autoPlay: true
		onStopped: play()
		fillMode: VideoOutput.PreserveAspectCrop 
	}
	Image {
		anchors.fill: parent
		source: "qrc:///camera.png"
	}
}