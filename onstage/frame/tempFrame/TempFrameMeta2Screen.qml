import QtQuick 2.7
import QtQuick.Controls 1.5

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
		width: 400
		height: 480
		Loader {
			id: loader0
			objectName: "loader0"
			anchors.fill: parent
		}
	}
	
	Item {
		id: mode1
		objectName: "mode1"
		x: 512
		y: 60
		width: 400
		height: 480
		Loader {
			id: loader1
			objectName: "loader1"
			anchors.fill: parent
		}
	}


	id: tempFrameMeta2Screen
	objectName: "tempFrameMeta2Screen"
	property var isLoaded: false
	signal loaded()

	Connections {
		target: mode0.item
		onLoaded: loadCheck()
	}

	Connections {
		target: mode1.item
		onLoaded: loadCheck()
	}

	function loadCheck() {
		if(isLoaded == false && 
			mode0.item.isLoaded == true && 
			mode1.item.isLoaded == true) {
			isLoaded = true;
			loaded();
		}
	}

}