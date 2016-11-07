#include <QtWebView\qtwebviewfunctions.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "frame\frame.h"
#include "socket\server_link.h"
#include <qstring.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QtWebView::initialize();
	WSocket::getInstance();

	// 启动websocket

	// 启动Frame
	string displayKind = "navi";
	int x = 0;
	int y = 0;
	if (argc == 4)
	{
		displayKind = argv[1];
		x = QString(argv[2]).toInt();
		y = QString(argv[3]).toInt();
	}
	Frame::getInstance()->initialize(QString::fromStdString(displayKind), x , y);

    return app.exec();
}
