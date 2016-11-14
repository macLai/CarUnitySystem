import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	width: 200
	height: 200
	Rectangle { anchors.fill: parent; color: "pink" }
	Text { text: "aircon_view0_half.qml" }

	property var isLoaded: false
	Component.onCompleted: {
		isLoaded = true;
		frame.loadCheck();
	}
}