#include "mode_data.h"
#include "audio\audio.h"
#include "camera\camera.h"
#include "navi\navi.h"
#include "crossroad\crossroad.h"
#include "opendoor\opendoor.h"
#include "phone\phone.h"
#include "acclda\acclda.h"
#include "driverinfo\driverinfo.h"
#include "energymonitor\energymonitor.h"
#include <qqmlapplicationengine.h>
#include "../frame/frame.h"

const QString ModeData::MODEID_AUDIO = "audio";
const QString ModeData::MODEID_NAVI = "navi";
const QString ModeData::MODEID_CAMERA = "camera";
const QString ModeData::MODEID_CROSSROAD = "crossroad";
const QString ModeData::MODEID_OPENDOOR = "opendoor";
const QString ModeData::MODEID_PHONE = "phone";
const QString ModeData::MODEID_ACCLDA = "acclda";
const QString ModeData::MODEID_DRIVERINFO = "driverinfo";
const QString ModeData::MODEID_ENERGYMONITOR = "energymonitor";

const QString ModeData::modeSize ( "{ \
	\"navi1\": { \
		\"0\": {\"x\": 0, \"y\": 0, \"width\": 800, \"height\": 480} \
	}, \
	\"navi2\": { \
		\"0\": {\"x\": 0, \"y\": 0, \"width\": 400, \"height\": 480}, \
		\"1\": {\"x\": 400, \"y\": 0, \"width\": 400, \"height\": 480} \
	}, \
	\"navi3\": { \
		\"0\": {\"x\": 0, \"y\": 0, \"width\": 400, \"height\": 480}, \
		\"1\": {\"x\": 400, \"y\": 0, \"width\": 400, \"height\": 240}, \
		\"2\": {\"x\": 400, \"y\": 240, \"width\": 400, \"height\": 240} \
	}, \
	\"meta1\": { \
		\"0\": {\"x\": 112, \"y\": 60, \"width\": 800, \"height\": 480} \
	}, \
	\"meta2\": { \
		\"0\": {\"x\": 112, \"y\": 60, \"width\": 400, \"height\": 480}, \
		\"1\": {\"x\": 512, \"y\": 60, \"width\": 400, \"height\": 480} \
	}, \
	\"meta3\": { \
		\"0\": {\"x\": 112, \"y\": 60, \"width\": 400, \"height\": 480}, \
		\"1\": {\"x\": 512, \"y\": 60, \"width\": 400, \"height\": 240}, \
		\"2\": {\"x\": 512, \"y\": 300, \"width\": 400, \"height\": 240} \
	}, \
	\"hud1\": { \
		\"0\": {\"x\": 634, \"y\": 518, \"width\": 300, \"height\": 300} \
	} \
}" );

ModeData* ModeData::it = NULL;

ModeBase *ModeData::getModeInstance(QString modeID)
{
	if (modeList.contains(modeID))
	{
		return modeList[modeID];
	}
	return NULL;
}

ModeData::ModeData()
{
	QQmlApplicationEngine* engine = Frame::getInstance()->getEngine();

	QObject *loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_AUDIO);
	if (loader != NULL) {
		modeList[MODEID_AUDIO] = Audio::getInstance(MODEID_AUDIO, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_CAMERA);
	if (loader != NULL) {
		modeList[MODEID_CAMERA] = Camera::getInstance(MODEID_CAMERA, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_NAVI);
	if (loader != NULL) {
		modeList[MODEID_NAVI] = Navi::getInstance(MODEID_NAVI, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_CROSSROAD);
	if (loader != NULL) {
		modeList[MODEID_CROSSROAD] = Crossroad::getInstance(MODEID_CROSSROAD, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_PHONE);
	if (loader != NULL) {
		modeList[MODEID_PHONE] = Phone::getInstance(MODEID_PHONE, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_OPENDOOR);
	if (loader != NULL) {
		modeList[MODEID_OPENDOOR] = Opendoor::getInstance(MODEID_OPENDOOR, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_ACCLDA);
	if (loader != NULL) {
		modeList[MODEID_ACCLDA] = Acclda::getInstance(MODEID_ACCLDA, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_DRIVERINFO);
	if (loader != NULL) {
		modeList[MODEID_DRIVERINFO] = Driverinfo::getInstance(MODEID_DRIVERINFO, loader);
	}

	loader = engine->rootObjects().first()->findChild<QObject*>(MODEID_ENERGYMONITOR);
	if (loader != NULL) {
		modeList[MODEID_ENERGYMONITOR] = Energymonitor::getInstance(MODEID_ENERGYMONITOR, loader);
	}
}

ModeData* ModeData::getInstance()
{
	if (it == NULL)
	{
		it = new ModeData();
	}
	return it;
}

QRect ModeData::getModeSize(QString displayKind, int len, int pos)
{
	QRect rect(-1, -1, 1, 1);
	QJsonObject data = QJsonDocument::fromJson(modeSize.toUtf8()).object();
	if (data.contains(displayKind + QString::number(len)))
	{
		QJsonObject dataNum = data[displayKind + QString::number(len)].toObject();
		if (dataNum.contains(QString::number(pos)))
		{
			rect.setX(dataNum[QString::number(pos)].toObject()["x"].toInt());
			rect.setY(dataNum[QString::number(pos)].toObject()["y"].toInt());
			rect.setWidth(dataNum[QString::number(pos)].toObject()["width"].toInt());
			rect.setHeight(dataNum[QString::number(pos)].toObject()["height"].toInt());
		}
	}
	return rect;
}

void ModeData::clearAllMode(QStringList ActiveModeList)
{
	QMapIterator<QString, ModeBase*> i(modeList);
	while (i.hasNext())
	{
		i.next();
		if (!ActiveModeList.contains(i.key()))
		{
			i.value()->endMode();
		}
	}
}