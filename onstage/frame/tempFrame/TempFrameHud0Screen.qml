import QtQuick 2.7
import QtQuick.Controls 1.5
import QtMultimedia 5.6

Item {
	id: frame
	objectName: "frame"
	property var isLoaded: false
	signal loaded()

	Video {
		id: video
		objectName: "video"
		property var isLoaded: false
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

		onStatusChanged: {
			if(status == MediaPlayer.Loaded && isLoaded == false) {
				isLoaded = true;
				tempFrameHud0Screen.loadCheck();
			}
		}
	}

	function loadCheck() {
		if(isLoaded == false &&
			video.isLoaded == true) {
			isLoaded = true;
			loaded();
		}
	}
}