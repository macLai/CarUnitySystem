#include "mode_enter.h"
#include "mode_data.h"
#include "../frame/frame_data.h"
#include <qobject.h>
#include <qstring.h>
#include <qlist.h>

ModeEnter* ModeEnter::it = NULL;

ModeEnter* ModeEnter::getInstance()
{
	if(it == NULL)
	{
		it = new ModeEnter();
	}
	return it;
}

void ModeEnter::initialize()
{

	ModeData::getInstance();
}

void ModeEnter::updateMode(QObject* target, QString activeModeListStr)
{
	QStringList activeModeList = activeModeListStr.split("|");

	ModeData *modeData = ModeData::getInstance();
	const int len = activeModeList.length();
	QList<QString> activeModeListBefore = modeData->getActiveModeList();
	

	for (int i = 0; i < len; i++)
	{

		QObject *modeTarget = target->findChild<QObject*>("mode" + QString::number(i));
		if (modeTarget == NULL) continue;

		modeData->setModeStatus(activeModeList[i], true, modeTarget);
	}

	for (int i = 0; i < activeModeListBefore.length(); i++)
	{
		if (!activeModeList.contains(activeModeListBefore[i]))
		{
			modeData->setModeStatus(activeModeListBefore[i], false, NULL);
		}
	}
}
