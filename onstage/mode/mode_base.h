#ifndef MODE_BASE_H
#define MODE_BASE_H

#include <string>
#include <qobject.h>
#include <qjsonobject.h>
#include <qstring.h>
#include "modeDB.h"
#include <qsize.h>
using namespace std;

class ModeBase
{
public:
	bool moveToPos(QObject* target);
	bool startMode(QObject* target);
	bool endMode();

protected:
	ModeBase(QString mode, QString modeDbData);
	
	ModeDB *viewDB;

private:
	bool transTo(QString target);
	bool getModeSize();

	QString modeID;
	QObject* displayTarget;
	QString currentView;
	QSize size;
};



#endif // !MODE_BASE_H