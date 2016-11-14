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

	property var target: "frameLoader1"
	signal loaded()

	Item {
		id: showedItem
		anchors.fill: parent
	}

	Loader {
		visible: false
		id: frameLoader1
		asynchronous: true
		objectName: "frameLoader1"
		anchors.fill: parent

		onLoaded: {
			if(target == "frameLoader1") {
				console.log("loaded")
				window.loaded();
			}
		}
	}

	Loader {
		visible: false
		id: frameLoader2
		asynchronous: true
		objectName: "frameLoader2"
		anchors.fill: parent

		onLoaded: {
			if(target == "frameLoader2") window.loaded();
		}
	}

	SequentialAnimation {
		id: loadedAnime
		objectName: "loadedAnime"
		PropertyAnimation {
			target: showedItem
			property: "opacity"
			to: 0
			duration: 1
			onStopped: {
				console.log("PropertyAnimation");
				if( window.target == "frameLoader1" ) {
					frameLoader1.item.parent = showedItem;
					window.target = "frameLoader2";
					frameLoader2.source = "";
				}
				else {
					frameLoader2.item.parent = showedItem;
					window.target = "frameLoader1";
					frameLoader1.source = "";
				}
			}
		}
		PropertyAnimation {
			target: showedItem
			property: "opacity"
			to: 1
		}
	}

	function loadeded() {
		console.log("PropertyAnimation")
		if( window.target == "frameLoader1" ) {
			frameLoader1.item.parent = showedItem;
			window.target = "frameLoader2";
			frameLoader2.source = "";
		}
		else {
			frameLoader2.item.parent = showedItem;
			window.target = "frameLoader1";
			frameLoader1.source = "";
		}
	}

	
}
