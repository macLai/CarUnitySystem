#include "frame.h"
#include <qtimer.h>
#include <qurl.h>
#include <qqmlcontext.h>
#include "../socket/server_link.h"


Frame* Frame::it = NULL;

void Frame::initialize(QString displayKind, int x, int y)
{
	if (isInitialized == true) return;
	isInitialized = true;

	

	this->displayKind = displayKind;

	engine.load(QUrl("qrc:///main.qml"));


	int width, height;
	FrameData::getDisplaySize(displayKind, width, height);
	engine.rootObjects().first()->setProperty("width", width);
	engine.rootObjects().first()->setProperty("height", height);
	engine.rootObjects().first()->setProperty("x", x);
	engine.rootObjects().first()->setProperty("y", y);
	engine.rootContext()->setContextProperty("wSocket", WSocket::getInstance());

	QObject *loader = engine.rootObjects().first()->findChild<QObject*>("frameLoader");
	connect(loader, SIGNAL(loaded()), this, SLOT(onFrameLoaded()));
	loader->setProperty("source", FrameData::getFrameLoader(displayKind));

	//qDebug() << QObject( engine.rootObjects()[0]).findChild("loader");

	connect(WSocket::getInstance(), &WSocket::frameChanged, this, &Frame::frameChanged);
}

Frame* Frame::getInstance()
{
	if (it == NULL)
	{
		it = new Frame();
	}
	return it;
}

void Frame::frameChanged(QString message)
{
	QJsonObject data = QJsonDocument::fromJson(message.toUtf8()).object();
	QString frame = data[displayKind].toObject()["frame"].toString();
	QString mode = data[displayKind].toObject()["mode"].toString();

	ModeEnter::getInstance()->updateMode(mode);
}

void Frame::onFrameLoaded()
{
	QObject *loader = engine.rootObjects().first()->findChild<QObject*>("frameLoader");
	if (displayKind == "hud")
	{
		engine.rootContext()->setContextProperty("car", WSocket::getInstance());
	}
	ModeEnter::getInstance()->initialize();

	WSocket::getInstance()->sendMenssage("{'action': 'getall'}");
}

QQmlApplicationEngine* Frame::getEngine()
{
	return &engine;
}

QString Frame::getDisplayKind()
{
	return displayKind;
}