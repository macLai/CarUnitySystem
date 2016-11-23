import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Rectangle {
		color: "black"
		anchors.fill: parent
	}
	
	Loader {
		id: audio
		objectName: "audio"
	}
	Loader {
		id: phone
		objectName: "phone"
	}
	Loader {
		id: navi
		objectName: "navi"
	}
}