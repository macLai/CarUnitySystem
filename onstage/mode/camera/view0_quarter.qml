import QtQuick 2.7
import QtQuick.Controls 1.5
import QtWebView 1.1

Item {
	WebView {
      anchors.fill: parent
      url: Qt.resolvedUrl("http://localhost:8888/map")
	}
}