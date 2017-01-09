#ifndef ENERGYMONITOR_H
#define ENERGYMONITOR_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "energymonitorDB.h"

using namespace std;

class Energymonitor :public ModeBase
{
public:
	Energymonitor(QString modeID, QObject *loader) :ModeBase(modeID, energymonitorDB, loader) {};
	static Energymonitor *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Energymonitor(modeID, loader);
		return it;
	};
	

private:
	static Energymonitor *it;
};

Energymonitor *Energymonitor::it = NULL;

#endif // !ENERGYMONITOR_H 