#ifndef AUDIO_H
#define AUDIO_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "audioDB.h"

using namespace std;

class Audio :public ModeBase
{
public:
	Audio(QString modeID) :ModeBase(modeID, audioDB) {};
	static Audio *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Audio(modeID);
		return it;
	};
	

private:
	static Audio *it;
};

Audio *Audio::it = NULL;

#endif // !AUDIO_H 