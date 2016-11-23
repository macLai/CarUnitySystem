#ifndef AUDIO_H
#define AUDIO_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "audioDB.h"

using namespace std;

class Audio :public ModeBase
{
public:
	Audio(QString modeID, QObject *loader) :ModeBase(modeID, audioDB, loader) {};
	static Audio *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Audio(modeID, loader);
		return it;
	};
	

private:
	static Audio *it;
};

Audio *Audio::it = NULL;

#endif // !AUDIO_H 