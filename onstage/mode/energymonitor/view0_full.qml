import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Image {
		source: "qrc:///ENERGYMONITOR_1.png"
	}

	Image {
		x: 633
		y: 1
		visible: device == "navi"
		source: backMouse.pressed? "qrc:///back_1_exe.png": "qrc:///back_1_nml.png"
		MouseArea {
			id: backMouse
			anchors.fill: parent
			onClicked: {
				wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'energymonitor'}");
			}
		}
	}
}