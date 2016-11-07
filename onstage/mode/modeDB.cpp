#include "modeDB.h"

ModeDB::ModeDB(QString dbData)
{
	dbJson = QJsonDocument::fromJson(dbData.toUtf8()).object();
}

QString ModeDB::getView(QString viewID, int width, int height)
{
	QString targetViewID;
	if (viewID == "default")
	{
		if (!dbJson.contains(viewID)) return NULL;
		targetViewID = dbJson[viewID].toString();
	}
	else
	{
		targetViewID = viewID;
	}


	QJsonObject targetViewDB = dbJson[targetViewID].toObject();
	QString viewKey = QString::number(width) + "|" + QString::number(height);
	if (!targetViewDB.contains(viewKey)) return NULL;

	return targetViewDB[viewKey].toString();
}