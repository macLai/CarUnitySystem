import QtQuick 2.7
import QtQuick.Controls 1.5
import QtWebView 1.1

Item {
	id: view0_full
	objectName: "view0_full"

	WebView {
	  id: webview
      anchors.fill: parent
      url: Qt.resolvedUrl("http://localhost:8888/map")

      onLoadingChanged: {
      	if(loading == false) {
      		console.log("onLoadingChanged")
      		view0_full.isLoaded = true;
			frame.loadCheck();
      	}
      }
	}

	property var isLoaded: false
}