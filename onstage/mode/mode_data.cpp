#include "mode_data.h"
#include "audio\audio.h"
#include "aircon\aircon.h"
#include "navi\navi.h"

const QString ModeData::MODEID_AUDIO = "audio";
const QString ModeData::MODEID_AIRCON = "aircon";
const QString ModeData::MODEID_NAVI = "navi";
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
	modeList[MODEID_AUDIO] = Audio::getInstance(MODEID_AUDIO);
	modeStatus[MODEID_AUDIO] = false;
	modeList[MODEID_AIRCON] = Aircon::getInstance(MODEID_AIRCON);
	modeStatus[MODEID_AIRCON] = false;
	modeList[MODEID_NAVI] = Navi::getInstance(MODEID_NAVI);
	modeStatus[MODEID_NAVI] = false;
}

ModeData* ModeData::getInstance()
{
	if (it == NULL)
	{
		it = new ModeData();
	}
	return it;
}

QList<QString> ModeData::getActiveModeList()
{
	QList<QString> ans;
	QMapIterator<QString, bool> i(modeStatus);
	while (i.hasNext())
	{
		i.next();
		if (i.value()) ans << i.key();
	}
	return ans;
}

bool ModeData::isModeActive(QString modeID)
{
	if (modeStatus.contains(modeID))
	{
		return modeStatus[modeID];
	}
	else return false;
}

bool ModeData::setModeStatus(QString modeID, bool status, QObject* target)
{
	if (!modeStatus.contains(modeID)) return false;
	else if (modeStatus[modeID] == false && status == false) return true;
	else if (modeStatus[modeID] == true && status == true)
	{
		if (modeList[modeID]->moveToPos(target)) return true;
		else return false;
	}
	else if (modeStatus[modeID] == false && status == true)
	{
		if (modeList[modeID]->startMode(target))
		{
			modeStatus[modeID] = status;
			return true;
		}
		else return false;
	}
	else if (modeStatus[modeID] == true && status == false)
	{
		if (modeList[modeID]->endMode())
		{
			modeStatus[modeID] = status;
			return true;
		}
		else return false;
	}
	return false;
}