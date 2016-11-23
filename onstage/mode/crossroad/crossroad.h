#ifndef CROSSROAD_H
#define CROSSROAD_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "crossroadDB.h"

using namespace std;

class Crossroad :public ModeBase
{
public:
	Crossroad(QString modeID, QObject *loader) :ModeBase(modeID, crossroadDB, loader) {};
	static Crossroad *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Crossroad(modeID, loader);
		return it;
	};
	

private:
	static Crossroad *it;
};

Crossroad *Crossroad::it = NULL;

#endif // !CROSSROAD_H 