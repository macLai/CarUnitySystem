import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
	id: window
	objectName: "window"
    visible: true
	x: 0
	y: 0
    width: 800
    height: 480
	flags: Qt.FramelessWindowHint

	property var device: "navi"

	Loader {
		id: frameLoader
		asynchronous: true
		objectName: "frameLoader"
		anchors.fill: parent
	}
}
