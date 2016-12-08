#include "server_link.h"
#include <qeventloop.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

WSocket* WSocket::it = NULL;

WSocket::WSocket():frameData(""), carStatus(true)
{
    QEventLoop loop;
    connect(this, &QWebSocket::connected, &loop, &QEventLoop::quit);
    open(QUrl("ws://localhost:8888"));
    loop.exec();
	disconnect(this, &QWebSocket::connected, &loop, &QEventLoop::quit);
	connect(this, &QWebSocket::textMessageReceived, this, &WSocket::reviceMessage);

}

WSocket *WSocket::getInstance()
{
	if (it == NULL) it = new WSocket();
	return it;
}

void WSocket::reviceMessage(QString message)
{
	QJsonObject data = QJsonDocument::fromJson(message.toUtf8()).object();
	QString status = data["status"].toString();
	if (status == "modelists")
	{
		if (frameData != message)
		{
			frameData = message;
			emit frameChanged(frameData);
		}
	}
	else if (status == "car")
	{
		QString run = data["run"].toString();
		bool carStatusLocal = (run == "start")?true:false;
		if (carStatusLocal != carStatus)
		{
			carStatus = carStatusLocal;
			emit carChanged(carStatus);
		}
	}
}

void WSocket::sendMenssage(QString data)
{
	sendTextMessage(data);
}

void WSocket::sendMessageFromQml(QString data)
{
	sendTextMessage(data);
}