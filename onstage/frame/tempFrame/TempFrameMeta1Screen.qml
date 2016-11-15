import QtQuick 2.7
import QtQuick.Controls 1.5
import QtMultimedia 5.6

Item {

	Rectangle {
		color: "black"
		anchors.fill: parent
	}

	Image {
		source: "../../pic/BK_L.png"
		x: 0
		y: 120
	}

	Image {
		source: "../../pic/BK_R.png"
		x: 912
		y: 120
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
}