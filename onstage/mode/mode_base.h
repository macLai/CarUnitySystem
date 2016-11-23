#ifndef MODE_BASE_H
#define MODE_BASE_H

#include <string>
#include <qobject.h>
#include <qjsonobject.h>
#include <qstring.h>
#include "modeDB.h"
#include <qsize.h>
#include <qrect.h>
#include <qpropertyanimation.h>
using namespace std;

class ModeBase:public QObject
{
	Q_OBJECT
public:
	bool moveToPos(QRect rect);
	bool startMode();
	bool endMode();

protected:
	ModeBase(QString mode, QString modeDbData, QObject *loader);
	
	ModeDB *viewDB;

private:
	bool transTo(QString target);
	bool getModeSize();

	QString modeID;
	QObject* displayTarget;
	QString currentView;
	QRect pos;
	QPropertyAnimation *showAnime;
	QPropertyAnimation *hideAnime;

private slots:
	bool setProperty();
};



#endif // !MODE_BASE_H