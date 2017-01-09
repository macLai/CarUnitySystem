#ifndef MODE_DATA_H
#define MODE_DATA_H

#include <qstringlist.h>
#include <QString>
#include <qmap.h>
#include <qobject.h>
#include <qlist.h>
#include "mode_base.h"
#include <qjsonobject.h>
#include <qrect.h>
#include <qstringlist.h>
using namespace std;

class ModeData
{
public:
	static ModeData* getInstance();
	ModeData();
	ModeBase *getModeInstance(QString modeID);
	QRect getModeSize(QString displayKind, int len, int pos);
	void clearAllMode(QStringList ActiveModeList);


	static const QString MODEID_AUDIO;
	static const QString MODEID_NAVI;
	static const QString MODEID_CAMERA;
	static const QString MODEID_CROSSROAD;
	static const QString MODEID_OPENDOOR;
	static const QString MODEID_PHONE;
	static const QString MODEID_ACCLDA;
	static const QString MODEID_DRIVERINFO;
	static const QString MODEID_ENERGYMONITOR;

private:
	static ModeData *it;
	QMap<QString, ModeBase*> modeList;

	static const QString modeSize;
};

#endif