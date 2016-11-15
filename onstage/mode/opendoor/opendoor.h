#ifndef OPENDOOR_H
#define OPENDOOR_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "opendoorDB.h"

using namespace std;

class Opendoor :public ModeBase
{
public:
	Opendoor(QString modeID) :ModeBase(modeID, opendoorDB) {};
	static Opendoor *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Opendoor(modeID);
		return it;
	};
	

private:
	static Opendoor *it;
};

Opendoor *Opendoor::it = NULL;

#endif // !OPENDOOR_H 