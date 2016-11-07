#ifndef AIRCON_H
#define AIRCON_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "airconDB.h"

using namespace std;

class Aircon :public ModeBase
{
public:
	Aircon(QString modeID) :ModeBase(modeID, airconDB) {};
	static Aircon *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Aircon(modeID);
		return it;
	};
	

private:
	static Aircon *it;
};

Aircon *Aircon::it = NULL;

#endif // !AIRCON_H 