#ifndef SERVER_LINK_H
#define SERVER_LINK_H

#include <qstring.h>
#include <QtWebSockets/QWebSocket>
#include <qobject.h>

const QString host = "http://127.0.0.1:5000";


class WSocket: public QWebSocket
{
	Q_OBJECT
public:
	static WSocket *getInstance();
	void sendMenssage(QString data);
	QString frameData;
	QString carStatus;
	bool lockStatus;
	bool phoneStatus;
	bool hudStatus;

public slots:
	void reviceMessage(QString message);
	void sendMessageFromQml(QString data);

signals:
	void frameChanged(QString message);
	void carChanged(QString carStatus);
	void lockChanged(bool lockStatus);
	void phoneChanged(bool phoneStatus);
	void hudLockChanged(bool hudStatus);

private:
	WSocket();
	~WSocket() {}

	static WSocket* it;
};

#endif