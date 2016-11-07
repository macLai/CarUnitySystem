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
	height: 240
	Loader {
		id: loader1
		objectName: "loader1"
		anchors.fill: parent
	}
}

Item {
	id: mode2
	objectName: "mode2"
	x: 512
	y: 300
	width: 400
	height: 240
	Loader {
		id: loader2
		objectName: "loader2"
		anchors.fill: parent
	}
}
}