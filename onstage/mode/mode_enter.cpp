#include "mode_enter.h"
#include "mode_data.h"
#include "../frame/frame_data.h"
#include "../frame/frame.h"
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

void ModeEnter::updateMode(QString activeModeListStr)
{
	QStringList activeModeList = activeModeListStr.split("|");

	ModeData *modeData = ModeData::getInstance();
	const int len = activeModeList.length();
	
	
	for (int i = 0; i < len; i++)
	{
		QRect rect = modeData->getModeSize(Frame::getInstance()->getDisplayKind(), len, i);

		ModeBase * target = modeData->getModeInstance(activeModeList[i]);
		if( target != NULL ) target->moveToPos(rect);
	}

	modeData->clearAllMode(activeModeList);
}
