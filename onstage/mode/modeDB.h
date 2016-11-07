#ifndef MODEDB_H
#define MODEDB_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <string>
using namespace std;

class ModeDB
{
public:
	ModeDB(QString dbData);
	QString getView(QString viewID, int width, int height);
private:
	QJsonObject dbJson;
};

#endif