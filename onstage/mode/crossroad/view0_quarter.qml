import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Image {
		source: "qrc:///Navi_1_4.png"
	}

	Image {
		x: 276
		y: 1
		visible: device == "navi"
		source: backMouse.pressed? "qrc:///back_1_4_exe.png": "qrc:///back_1_4_nml.png"
		MouseArea {
			id: backMouse
			anchors.fill: parent
			onClicked: {
				wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'crossroad'}");
			}
		}
	}
}