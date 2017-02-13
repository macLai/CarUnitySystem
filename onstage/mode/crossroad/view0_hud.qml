import QtQuick 2.7
import QtQuick.Controls 1.5

Item {
	Image {
		x: 7
		y: 28
		source: "qrc:///crossroad.png"
	}

	Text {
		text: 'ZhangJiang\nNorth\nRoad'
		x: 52
		y: 31
		font.pixelSize: 17
		font.weight: Font.DemiBold
		color: "white"
	}
}