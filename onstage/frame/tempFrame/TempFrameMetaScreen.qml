import QtQuick 2.7
import QtQuick.Controls 1.5

Item {

	Rectangle {
		color: "black"
		anchors.fill: parent
	}

	Image {
		source: "qrc:///BK_L.png"
		x: 0
		y: 120
	}

	Image {
		source: "qrc:///BK_R.png"
		x: 912
		y: 120
	}

	Loader {
		id: audio
		objectName: "audio"
	}
	Loader {
		id: camera
		objectName: "camera"
	}
	Loader {
		id: crossroad
		objectName: "crossroad"
	}
	Loader {
		id: opendoor
		objectName: "opendoor"
	}
	Loader {
		id: phone
		objectName: "phone"
	}
}