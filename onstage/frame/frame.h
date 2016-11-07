#ifndef FRAME_H
#define FRAME_H
#include <QQmlApplicationEngine>
#include <qstring.h>
#include "frame_data.h"
#include "../mode/mode_enter.h"
#include <QDebug>
#include <qeventloop.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qobject.h>
#include <qtimer.h>

using namespace std;

class Frame:public QObject
{
    Q_OBJECT
public:
	static Frame *getInstance();
	void initialize(QString displayKind, int x, int y);
	void updateFrame(QString frame, QString modes);
private:
	static Frame *it;
    Frame() :QObject(0), isInitialized(false), selectedFrame(""), displayKind(""), modes(""){}

	QQmlApplicationEngine engine;
	bool isInitialized;
	QString selectedFrame;
	QString displayKind;
	QString modes;

public slots:
	void frameChanged(QString message);
	void onFrameLoaded();
};

#endif