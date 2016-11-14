import QtQuick 2.7
import QtQuick.Controls 1.5
import QtMultimedia 5.6

Item {

	Item {
		x: 0
		y: 0
		width: 1024
		height: 600
	}
	
	Item {
		id: mode0
		objectName: "mode0"
		x: 112
		y: 60
		width: 800
		height: 480
		Loader {
			id: loader0
			objectName: "loader0"
			anchors.fill: parent
		}
	}


	id: frame
	objectName: "frame"
	property var isLoaded: false
	signal loaded()

	Connections {
		target: mode0.item
		onLoaded: loadCheck()
	}

	function loadCheck() {
		if( isLoaded == false && 
			mode0.item.isLoaded == true) {
			isLoaded = true;
			loaded();
		}
	}
}