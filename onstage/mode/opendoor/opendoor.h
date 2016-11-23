#ifndef OPENDOOR_H
#define OPENDOOR_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "opendoorDB.h"

using namespace std;

class Opendoor :public ModeBase
{
public:
	Opendoor(QString modeID, QObject *loader) :ModeBase(modeID, opendoorDB, loader) {};
	static Opendoor *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Opendoor(modeID, loader);
		return it;
	};

private:
	static Opendoor *it;
};

Opendoor *Opendoor::it = NULL;

#endif // !OPENDOOR_H 