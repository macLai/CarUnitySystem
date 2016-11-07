#ifndef MODE_DATA_H
#define MODE_DATA_H

#include <qstringlist.h>
#include <QString>
#include <qmap.h>
#include <qobject.h>
#include <qlist.h>
#include "mode_base.h"
using namespace std;

class ModeData
{
public:
	static ModeData* getInstance();
	ModeData();
	ModeBase *getModeInstance(QString modeID);
	bool isModeActive(QString modeID);
	QList<QString> getActiveModeList();
	bool setModeStatus(QString modeID, bool status, QObject* target);


	static const QString MODEID_AUDIO;
	static const QString MODEID_NAVI;
	static const QString MODEID_AIRCON;

private:
	static ModeData *it;
	QMap<QString, ModeBase*> modeList;
	QMap<QString, bool> modeStatus;
};

#endif