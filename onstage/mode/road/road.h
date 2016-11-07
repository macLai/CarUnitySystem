#ifndef ROAD_H
#define ROAD_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "roadDB.h"

using namespace std;

class Road :public ModeBase
{
public:
	Road(QString modeID) :ModeBase(modeID, roadDB) {};
	static Road *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Road(modeID);
		return it;
	};
	

private:
	static Road *it;
};

Road *Road::it = NULL;

#endif // !ROAD_H 