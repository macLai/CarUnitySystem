#ifndef CROSSROAD_H
#define CROSSROAD_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "crossroadDB.h"

using namespace std;

class Crossroad :public ModeBase
{
public:
	Crossroad(QString modeID) :ModeBase(modeID, crossroadDB) {};
	static Crossroad *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Crossroad(modeID);
		return it;
	};
	

private:
	static Crossroad *it;
};

Crossroad *Crossroad::it = NULL;

#endif // !CROSSROAD_H 