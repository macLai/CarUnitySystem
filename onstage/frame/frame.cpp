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

	engine.load(QUrl(QStringLiteral("frame/main.qml")));


	int width, height;
	FrameData::getFrameSize(displayKind, width, height);
	engine.rootObjects().first()->setProperty("width", width);
	engine.rootObjects().first()->setProperty("height", height);
	engine.rootObjects().first()->setProperty("x", x);
	engine.rootObjects().first()->setProperty("y", y);

	QObject *loader = engine.rootObjects().first()->findChild<QObject*>("frameLoader");
	connect(loader, SIGNAL(loaded()), this, SLOT(onFrameLoaded()));

	//qDebug() << QObject( engine.rootObjects()[0]).findChild("loader");

	ModeEnter::getInstance()->initialize();


	connect(WSocket::getInstance(), &WSocket::frameChanged, this, &Frame::frameChanged);
	WSocket::getInstance()->sendMenssage("{'action': 'getall'}");
}

Frame* Frame::getInstance()
{
	if (it == NULL)
	{
		it = new Frame();
	}
	return it;
}

void Frame::updateFrame(QString frame, QString modes)
{
	QObject *loader = engine.rootObjects().first()->findChild<QObject*>("frameLoader");

	if (selectedFrame != frame)
	{

		QString frameLoader = FrameData::getFrameLoader(frame);
		if (frameLoader == NULL) return;


		this->modes = modes;
		loader->setProperty("source", frameLoader);
		selectedFrame = frame;
		
	}
	else
	{

		if (this->modes != modes)
		{
			ModeEnter::getInstance()->updateMode(loader, modes);
			this->modes = modes;
		}
	}
}

void Frame::frameChanged(QString message)
{
	QJsonObject data = QJsonDocument::fromJson(message.toUtf8()).object();
	QString frame = data[displayKind].toObject()["frame"].toString();
	QString mode = data[displayKind].toObject()["mode"].toString();

	updateFrame(frame, mode);
}

void Frame::onFrameLoaded()
{
	QObject *loader = engine.rootObjects().first()->findChild<QObject*>("frameLoader");
	if (displayKind == "hud")
	{
		engine.rootContext()->setContextProperty("car", WSocket::getInstance());
	}

	ModeEnter::getInstance()->updateMode(loader, modes);
}
