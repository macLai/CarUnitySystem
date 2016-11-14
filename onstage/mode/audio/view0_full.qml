import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Rectangle { anchors.fill: parent; color: "green" }
	Text { text: "audio_view0_full.qml" }

	property var isLoaded: false
	Component.onCompleted: {
		isLoaded = true;
		frame.loadCheck();
	}
}