import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Image {
		source: "qrc:///DriverInfo_1_2.png"
	}

	Image {
		x: 239
		y: 1
		visible: device == "navi"
		source: backMouse.pressed? "qrc:///back_1_2_exe.png": "qrc:///back_1_2_nml.png"
		MouseArea {
			id: backMouse
			anchors.fill: parent
			onClicked: {
				wSocket.sendMessageFromQml("{'action': 'modeoff', 'mode': 'driverinfo'}");
			}
		}
	}
}