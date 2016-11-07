import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import QtWebView 1.1

ApplicationWindow {
	id: window
	objectName: "window"
    visible: true
	x: 0
	y: 0
    width: 800
    height: 480
	flags: Qt.FramelessWindowHint

	Loader {
		id: frameLoader
		asynchronous: true
		objectName: "frameLoader"
		anchors.fill: parent
	}

	// Rectangle { width: 80; height: 50; color: "red" }
	// WebView {
 //      anchors.fill: parent
 //      url: Qt.resolvedUrl("http://localhost:8888/map")
	// }
}
